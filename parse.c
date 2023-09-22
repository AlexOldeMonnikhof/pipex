/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:41:17 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 15:24:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	parse_envp(t_pipex *pipex, char **envp)
{
	char	*path;

	path = get_path(envp);
	if (!path)
		ft_error("Error: path not located, restart terminal");
	if (ft_strlen(path) > 5)
		pipex->paths = ft_split(path + 5, ':');
	if (!pipex->paths)
		ft_error("split error");
}

char	*get_right_path(t_pipex *pipex, char **envp, int cmd)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i])
	{
		if (cmd == 0)
			ret = ft_strjoin2(envp[i], pipex->cmd1[0]);
		else
			ret = ft_strjoin2(envp[i], pipex->cmd2[0]);
		if (access(ret, X_OK | F_OK) == 0)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}

void	parse_right_paths(t_pipex *pipex)
{
	pipex->right_paths = (char **)malloc(3 * sizeof(char *));
	if (!pipex->right_paths)
		ft_error("malloc error");
	pipex->right_paths[0] = get_right_path(pipex, pipex->paths, 0);
	pipex->right_paths[1] = get_right_path(pipex, pipex->paths, 1);
	pipex->right_paths[2] = NULL;
}

void	parse_cmds(t_pipex *pipex, char **argv)
{
	if (ft_strnstr(argv[2], "grep", 4) || ft_strnstr(argv[2], "awk", 3))
		pipex->cmd1 = ft_split2(argv[2], ' ');
	else
		pipex->cmd1 = ft_split(argv[2], ' ');
	if (ft_strnstr(argv[3], "grep", 4) || ft_strnstr(argv[3], "awk", 3))
		pipex->cmd2 = ft_split2(argv[3], ' ');
	else
		pipex->cmd2 = ft_split(argv[3], ' ');
}

void	parse_all(t_pipex *pipex, int argc, char **argv, char **envp)
{
	check_input(argc, argv);
	pipex->fd[INFILE] = open(argv[1], O_RDONLY);
	if (pipex->fd[INFILE] < 0)
		ft_errno("infile");
	pipex->fd[OUTFILE] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd[OUTFILE] < 0)
		ft_errno("outfile");
	parse_cmds(pipex, argv);
	parse_envp(pipex, envp);
	parse_right_paths(pipex);
}
