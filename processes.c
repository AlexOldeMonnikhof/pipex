/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:39:41 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 15:24:21 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	child_prc(t_pipex *pipex, char **envp)
{
	if (!pipex->right_paths[0])
		ft_error("cmd1 not found");
	if (dup2(pipex->fd[READ_END], STDIN_FILENO) == -1)
		ft_errno("dup2");
	if (dup2(pipex->end[WRITE_END], STDOUT_FILENO) == -1)
		ft_errno("dup2");
	close(pipex->end[READ_END]);
	close(pipex->fd[WRITE_END]);
	if (execve(pipex->right_paths[0], pipex->cmd1, envp) == -1)
		ft_errno("execve cmd1");
}

void	parent_prc(t_pipex *pipex, char **envp)
{
	if (!pipex->right_paths[1])
		ft_error("cmd2 not found");
	if (dup2(pipex->fd[WRITE_END], STDOUT_FILENO) == -1)
		ft_errno("dup2");
	if (dup2(pipex->end[READ_END], STDIN_FILENO) == -1)
		ft_errno("dup2");
	close(pipex->end[WRITE_END]);
	close(pipex->fd[READ_END]);
	if (execve(pipex->right_paths[1], pipex->cmd2, envp) == -1)
		ft_errno("execve cmd2");
}
