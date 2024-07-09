/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:14:08 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/08 14:41:05 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_unset(t_shell *shell, char *var)
{
	size_t	index;

	index = find_env_index(shell->env, var);
	printf("%ld\n", index);
	free(shell->env[index]);
	while (shell->env[index] != NULL)
	{
		shell->env[index] = shell->env[index + 1];
		index++;
	}
}
