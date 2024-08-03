/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:08:54 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/03 23:25:53 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !ft_isalpha(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		if (str[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

static int av_count(char **av)
{
	int i;

	i = 0;
	while(av[i])
		i++;
	return (i);
}

void mini_export(t_shell *shell, char **argv)
{
	int		i;
	int		j;
	size_t	len;
	char	*equals_check;
	char	*identifier;
	char	*new_env_var;
	int		var_found;
	char	*env_var;
	int		env_count;
	char	**new_env;

	i = 1;
	while (argv[i])
	{
		equals_check = strchr(argv[i], '=');
		if (!equals_check)
		{
			printf("export: not an identifier: %s\n", argv[i]);
			i++;
			continue ;
		}
		identifier = strndup(argv[i], equals_check - argv[i]);
		if (!identifier)
			return ;
		if (!valid_identifier(identifier))
		{
			printf("export: not an identifier: %s\n", argv[i]);
			free(identifier);
			i++;
			continue ;
		}
		var_found = 0;
		j = 0;
		while (shell->env[j])
		{
			env_var = strchr(shell->env[j], '=');
			if (env_var)
			{
				len = env_var - shell->env[j];
				if (strncmp(identifier, shell->env[j], len) == 0 && strlen(identifier) == len)
				{
					free(shell->env[j]);
					new_env_var = strdup(argv[i]);
					if (!new_env_var)
					{
						free(identifier);
						return ;
					}
					shell->env[j] = new_env_var;
					var_found = 1;
					break ;
				}
			}
			j++;
		}
		if (!var_found)
		{
			env_count = 0;
			while (shell->env[env_count])
				env_count++;
			new_env = malloc(sizeof(char *) * (env_count + 2));
			if (!new_env)
			{
				free(identifier);
				return;
			}
			j = 0;
			while (j < env_count)
			{
				new_env[j] = shell->env[j];
				j++;
			}
			new_env[env_count] = strdup(argv[i]);
			if (!new_env[env_count])
			{
				free(new_env);
				free(identifier);
				return;
			}
			new_env[env_count + 1] = NULL;
			free(shell->env);
			shell->env = new_env;
		}
		free(identifier);
		i++;
	}
}


//------------------------------------------
/*
int find_variable(t_shell *shell, char *identifier, char *arg)
{
	int j = 0;
	while (shell->env[j])
	{
		char *env_var = strchr(shell->env[j], '=');
		if (env_var)
		{
			size_t len = env_var - shell->env[j];
			if (strncmp(identifier, shell->env[j], len) == 0 && strlen(identifier) == len)
			{
				free(shell->env[j]);
				char *new_env_var = strdup(arg);
				if (!new_env_var)
					return 0;
				shell->env[j] = new_env_var;
				return 1;
			}
		}
		j++;
	}
	return 0;
}

void add_variable(t_shell *shell, char *arg)
{
	int env_count = 0;
	while (shell->env[env_count])
		env_count++;
	char **new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		return;
	int j = 0;
	while (j < env_count)
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[env_count] = strdup(arg);
	if (!new_env[env_count])
	{
		free(new_env);
		return;
	}
	new_env[env_count + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void print_environment(t_shell *shell)
{
	int i = 0;
	while (shell->env[i])
	{
		printf("envler: %s\n", shell->env[i]);
		i++;
	}
}

int process_argument(t_shell *shell, char *arg)
{
	char *equals_check = strchr(arg, '=');
	if (!equals_check)
	{
		printf("export: not an identifier: %s\n", arg);
		return 0;
	}
	char *identifier = strndup(arg, equals_check - arg);
	if (!identifier)
		return 0;
	if (!valid_identifier(identifier))
	{
		printf("export: not an identifier: %s\n", arg);
		free(identifier);
		return 0;
	}
	int var_found = find_variable(shell, identifier, arg);
	if (!var_found)
		add_variable(shell, arg);
	free(identifier);
	return 1;
}

void mini_export(t_shell *shell, char **argv)
{
	int i = 1;
	while (argv[i])
	{
		if (!process_argument(shell, argv[i]))
		{
			i++;
			continue;
		}
		i++;
	}
	print_environment(shell);
}
*/
