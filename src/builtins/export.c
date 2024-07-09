/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:08:54 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/06 16:17:43 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_accepted(int c)
{
	if (ft_isalpha(c))
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

void	mini_export(t_shell *shell, char **argv)
{
	char	*var;
	size_t	var_size;
	char	*value;
	size_t	value_size;

	if (argv[1] == NULL)
		return ;
	var_size = (int)(ft_strchr(argv[1], '=') - argv[1]);
	if (var_size <= 0)
		return ;
	var = ft_substr(argv[1], 0, var_size);
	if (!ft_isdigit(var[0]) && ft_strcheck(var, is_accepted))
	{
		value_size = ft_strlen(argv[1]) - var_size;
		value = ft_substr(ft_strchr(argv[1], '='), 1, value_size);
		set_env(shell->env, var, value);
		free(value);
	}
	free(var);
}
