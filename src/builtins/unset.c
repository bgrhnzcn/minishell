/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:14:08 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/03 23:34:50 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_unset(t_shell *shell, char **argv)
{
	int		i;
	int		j;
	int		env_size;
	int		found;
	char	**new_env;

	j = 0;
	i = 0;
	found = 0;
	env_size = 0;
	if (!shell || !argv || !argv[1])
		return ;
	while (shell->env[env_size])
		env_size++;
	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return ;
	while (i < env_size)
	{
		if (strcmp(shell->env[i], argv[1]) == 0)
		{
			free(shell->env[i++]);
			found = 1;
		}
		else
			new_env[j++] = shell->env[i++];
	}
	new_env[j] = NULL;
	if (found)
		free(shell->env);
	shell->env = new_env;
}
