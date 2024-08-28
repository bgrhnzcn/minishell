/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:14:08 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/28 15:18:31 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	counter_argv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

void	mini_unset(t_shell *shell, char **argv)
{
	int		i;
	char	*var;

	g_global_exit = 0;
	if (!shell || !argv)
		return ;
	i = 1;
	while (argv[i])
	{
		var = get_env(shell->env, argv[i]);
		if (!valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier \n", STDERR_FILENO);
			g_global_exit = 1;
		}
		else if (!ft_strequ(var, ""))
			remove_env(shell, argv[i]);
		i++;
		free(var);
	}
}
