/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:53:03 by olyetisk          #+#    #+#             */
/*   Updated: 2024/08/03 23:28:47 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_echo(char *s)
{
	if (!*s)
		return (false);
	if (*s == '-' && *(s + 1))
	{
		while (*s == '-')
			s++;
		s++;
		while (*s == 'n')
			s++;
	}
	if (*s)
		return (false);
	return (true);
}

void	mini_echo(char **av)
{
	t_bool	flg;

	av++;
	flg = false;
	while (*av && check_echo(*av))
	{
		flg = 1;
		av++;
	}
	while (*av)
	{
		ft_putstr_fd(*av++, 1);
		if (*av)
			ft_putstr_fd(" ", 1);
	}
	if (!flg)
		ft_putstr_fd("\n", 1);
}
