/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:55:28 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 15:24:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->paths[i++])
		free(pipex->paths[i - 1]);
	free(pipex->paths);
}

char	*get_path(char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i])
	{
		ret = ft_strnstr(envp[i], "PATH=", 5);
		if (ret)
			return (ret);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		i;
	int		j;
	size_t	total_len;
	char	*new_str;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(total_len * sizeof(char) + 2);
	if (!new_str)
		return (NULL);
	while (s1[i++])
		new_str[i - 1] = s1[i - 1];
	new_str[i - 1] = '/';
	while (s2[j++])
		new_str[i++] = s2[j - 1];
	new_str[i] = '\0';
	return (new_str);
}
