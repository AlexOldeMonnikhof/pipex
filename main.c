/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:07:23 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 15:24:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	pipe_and_fork(t_pipex *pipex, char **envp)
{
	pid_t	id;

	if (pipe(pipex->end) < 0)
		ft_errno("pipe");
	id = fork();
	if (id < 0)
		ft_errno("fork");
	if (id == 0)
		child_prc(pipex, envp);
	else
		parent_prc(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	parse_all(&pipex, argc, argv, envp);
	ft_free(&pipex);
	pipe_and_fork(&pipex, envp);
	return (0);
}
