/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:19:35 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/09/22 15:24:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input(int argc, char **argv)
{
	if (argc != 5)
		ft_error("invalid number of arguments...");
	if (!argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0])
		ft_error("empty string(s)...");
}
