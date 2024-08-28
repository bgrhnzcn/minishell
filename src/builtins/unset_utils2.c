/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:07:11 by olyetisk          #+#    #+#             */
/*   Updated: 2024/08/28 14:51:37 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env_variable(t_shell *shell, const char *arg, int *found)
{
	int		i;
	int		j;
	int		env_size;
	char	**new_env;

	i = 0;
	j = 0;
	*found = 0;
	env_size = count_env_variables(shell->env);
	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return (NULL);
	while (i < env_size)
	{
		if (ft_strlen(arg) == counter_argv(shell->env[i])
			&& !ft_strncmp(shell->env[i], arg, counter_argv(shell->env[i])))
		{
			free(shell->env[i]);
			*found = 1;
		}
		else
			new_env[j++] = shell->env[i++];
	}
	new_env[j] = NULL;
	return (new_env);
}
