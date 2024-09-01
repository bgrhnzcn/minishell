/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:30 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/01 19:31:19 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_index(char **env, char *var)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (i < ft_strarrlen(env))
	{
		temp = ft_substr(env[i], 0, (int)(ft_strchr(env[i], '=') - env[i]));
		if (temp == NULL)
			return (-1);
		if (ft_strequ(temp, var))
			return (free(temp), i);
		free(temp);
		i++;
	}
	return (-1);
}

char	*get_env(char **env, char *var)
{
	char	*res;
	int		i;

	i = find_env_index(env, var);
	if (i == -1)
		return (ft_strdup(""));
	res = ft_strdup(env[i]);
	if (res == NULL)
		return (ft_strdup(""));
	return (res);
}

void	set_env(char **env, char *var, char *value)
{
	char	*temp;
	int		i;
	size_t	env_size;

	i = ft_strarrlen(env);
	env_size = ft_strlen(var) + ft_strlen(value) + 2;
	temp = get_env(env, var);
	if (ft_strequ(temp, ""))
	{
		free(temp);
		return ;
	}
	else
	{
		i = find_env_index(env, var);
		free(temp);
	}
	free(env[i]);
	env[i] = ft_calloc(env_size, sizeof(char));
	ft_strlcat(env[i], var, env_size);
	ft_strlcat(env[i], "=", env_size);
	ft_strlcat(env[i], value, env_size);
	if (temp == NULL)
		env[i + 1] = NULL;
}

int	init_env(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	shell->env = ft_calloc(ENV_LIMIT, sizeof (char *));
	if (shell->env == NULL)
		return (1);
	while (envp[i] != NULL && i < ENV_LIMIT)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (shell->env[i] == NULL)
			return (ft_free_str_arr(shell->env), 1);
		i++;
	}
	shell->env[i] = NULL;
	return (0);
}

void	mini_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
