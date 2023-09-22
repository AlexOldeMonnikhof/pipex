/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:57:24 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 15:24:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

size_t	ft_wrd_count2(const char *s, char c)
{
	size_t	wrd_count;
	size_t	i;

	wrd_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			wrd_count++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (wrd_count);
}

int	ft_count_quotes(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			count++;
		i++;
	}
	if (count == 1)
		ft_error("Error: invalid grep or awk");
	return (count);
}

char	*quotes(char const *s, size_t *wrd_len, size_t *wrd_count)
{
	char	*ret;
	int		quote_count;
	int		j;

	j = 0;
	quote_count = ft_count_quotes(s);
	if (quote_count == 0)
		return (ft_substr(s, 0, *wrd_len));
	while (quote_count > 0)
	{
		if (s[j] == '\"' || s[j] == '\'')
			quote_count--;
		if (s[j] == ' ')
		{
			(*wrd_count)--;
			while (s[j + 1] == ' ')
				j++;
		}
		j++;
	}
	ret = ft_substr(s, 1, j - 2);
	*wrd_len += (j - 5);
	return (ret);
}

char	**ft_make_arr2(char **str, char const *s, char c, size_t wrd_count)
{
	size_t	wrd_len;
	size_t	i;

	i = 0;
	while (i < wrd_count)
	{
		wrd_len = 0;
		while (*s == c)
			s++;
		while (s[wrd_len] != c && s[wrd_len])
			wrd_len++;
		if (i == 1)
			str[i] = quotes(s, &wrd_len, &wrd_count);
		else
			str[i] = ft_substr(s, 0, wrd_len);
		if (!str[i])
			ft_errno("malloc");
		s += wrd_len;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split2(char const *s, char c)
{
	char	**str;
	size_t	wrd_count;

	if (!s)
		return (NULL);
	wrd_count = ft_wrd_count2(s, c);
	str = (char **)malloc((wrd_count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	str[wrd_count] = NULL;
	str = ft_make_arr2(str, s, c, wrd_count);
	return (str);
}
