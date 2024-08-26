/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:02:40 by olyetisk          #+#    #+#             */
/*   Updated: 2024/08/26 19:08:35 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	find_existing_env_var(t_shell *shell, const char *identifier)
{
	int		j;
	size_t	len;
	char	*env_var;

	j = 0;
	while (shell->env[j])
	{
		env_var = strchr(shell->env[j], '=');
		if (env_var)
		{
			len = env_var - shell->env[j];
			if (ft_strncmp(identifier, shell->env[j], len) == 0
				&& ft_strlen(identifier) == len)
				return (j);
		}
		j++;
	}
	return (-1);
}

static	int	update_env_var(t_shell *shell, int j, const char *arg)
{
	char	*new_env_var;

	free(shell->env[j]);
	new_env_var = ft_strdup(arg);
	if (!new_env_var)
		return 0;
	shell->env[j] = new_env_var;
	return (1);
}

int	check_env(t_shell *shell, const char *identifier, const char *arg)
{
	int j;

	j = find_existing_env_var(shell, identifier); // Identifier'ın indis yerini bul
	if (j != -1)
		return (update_env_var(shell, j, arg)); // Eğer indeks bulunduysa, değişkeni güncelle
	return 0; // Eğer identifier bulunamazsa 0 döndür
}
int	add_new_env(t_shell *shell, const char *arg)
{
	int		env_count;
	char	**new_env;

	env_count = 0;
	while (shell->env[env_count])
		env_count++;
	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (0);
	for (int j = 0; j < env_count; j++)
		new_env[j] = shell->env[j];
	new_env[env_count] = ft_strdup(arg);
	if (!new_env[env_count])
	{
		free(new_env);
		return (0);
	}
	new_env[env_count + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (1);
}