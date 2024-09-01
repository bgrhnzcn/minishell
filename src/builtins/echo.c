/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:53:03 by olyetisk          #+#    #+#             */
/*   Updated: 2024/08/28 19:19:45 by olyetisk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo(char *s)
{
	int	i;

	if (s == NULL || strlen(s) < 2)
		return (0);
	if (s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	mini_echo(char **av)
{
	int	new;
	int	i;

	new = 0;
	i = 1;
	while (av[i] && check_echo(av[i]))
	{
		new = 1;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		i++;
		if (av[i])
			ft_putstr_fd(" ", 1);
	}
	if (!new)
		ft_putstr_fd("\n", 1);
}
