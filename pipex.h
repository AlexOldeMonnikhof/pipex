/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:33 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 15:22:28 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef struct pipex{
	int		fd[2];
	int		end[2];
	char	**right_paths;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
}			t_pipex;

enum e_enums{
	READ_END = 0,
	WRITE_END = 1,
	INFILE = 0,
	OUTFILE = 1,
};

//MAIN
void	pipe_and_fork(t_pipex *pipex, char **envp);
int		main(int argc, char **argv, char **envp);

//CHECK
char	*parse_cmd(t_pipex *pipex, char **envp, int cmd);
void	check_input(int argc, char **argv);

//PARSE
void	parse_envp(t_pipex *pipex, char **envp);
char	*get_right_path(t_pipex *pipex, char **envp, int cmd);
void	parse_right_paths(t_pipex *pipex);
void	parse_all(t_pipex *pipex, int argc, char **argv, char **envp);

//ERROR
void	ft_errno(char *msg);
void	ft_error(char *msg);

//PROCCESSES
void	child_prc(t_pipex *pipex, char **envp);
void	parent_prc(t_pipex *pipex, char **envp);

//UTILS
char	*get_path(char **envp);
void	ft_leaks(void);
void	ft_free(t_pipex *pipex);
char	*ft_strjoin2(char const *s1, char const *s2);

//SPLIT2
size_t	ft_wrd_count2(const char *s, char c);
int		ft_count_quotes(char const *s);
char	*quotes(char const *s, size_t *wrd_len, size_t *wrd_count);
char	**ft_make_arr2(char **str, char const *s, char c, size_t wrd_count);
char	**ft_split2(char const *s, char c);

#endif