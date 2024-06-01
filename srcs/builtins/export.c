/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:08:54 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/01 17:27:05 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_export(t_shell *shell, char **argv)
{
	char	*var;
	size_t	var_size;
	char	*value;
	size_t	value_size;

	if (argv[1] == NULL)
		return ;
	var_size = (int)(ft_strchr(argv[1], '=') - argv[1]);
	var = ft_substr(argv[1], 0, var_size);
	value_size = ft_strlen(argv[1]) - var_size;
	value = ft_substr(ft_strchr(argv[1], '='), 1, value_size);
	set_env(shell->env, var, value);
}
