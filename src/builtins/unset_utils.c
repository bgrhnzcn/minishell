/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:53:41 by olyetisk          #+#    #+#             */
/*   Updated: 2024/08/28 15:17:32 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_variables(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

static	void	finalize_new_env(t_shell *shell, char **new_env, int found)
{
	if (found)
	{
		free(shell->env);
		shell->env = new_env;
	}
	else
		free(new_env);
}

char	**envs(int size)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (NULL);
	return (new_env);
}

void	remove_env(t_shell *shell, const char *arg)
{
	int		i;
	int		j;
	int		env_size;
	int		found;
	char	**new_env;

	i = 0;
	j = 0;
	found = 0;
	env_size = count_env_variables(shell->env);
	new_env = envs(env_size);
	while (i < env_size)
	{
		if (ft_strlen(arg) == counter_argv(shell->env[i])
			&& !ft_strncmp(shell->env[i], arg, counter_argv(shell->env[i])))
		{
			free(shell->env[i++]);
			found = 1;
		}
		else
			new_env[j++] = shell->env[i++];
	}
	new_env[j] = NULL;
	finalize_new_env(shell, new_env, found);
}
