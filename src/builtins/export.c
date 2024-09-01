/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:08:54 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/29 17:17:07 by olyetisk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_identifier(const char *str)
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
	if ((str[i] == '=' && str[i + 1] == '\0')
		|| (str[i] == '=' && str[i + 1] != '\0'))
		return (0);
	return (1);
}

static	char	*get_identifier(char *arg, char **equals_check)
{
	char	*identifier;

	*equals_check = ft_strchr(arg, '=');
	identifier = ft_substr(arg, 0, *equals_check - arg);
	if (!identifier || !valid_identifier(identifier))
	{
		free(identifier);
		return (NULL);
	}
	return (identifier);
}

static int	identifier_error(char **argv, char *identifier, int *i)
{
	if (!identifier)
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(argv[*i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_global_exit = 1;
		(*i)++;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	mini_export_hlpr(t_shell *shell, char **argv,
	int i, char *identifier)
{
	if (!check_env(shell, identifier, argv[i]))
	{
		if (!add_new_env(shell, argv[i]))
		{
			free (identifier);
			return ;
		}
	}
	free (identifier);
}

void	mini_export(t_shell *shell, char **argv, int i, char *identifier)
{
	char	*equals_check;

	while (argv[i])
	{
		identifier = get_identifier(argv[i], &equals_check);
		if (identifier_error(argv, identifier, &i))
			continue ;
		if (equals_check == NULL)
		{
			free(identifier);
			i++;
			continue ;
		}
		if (argv[i] != identifier)
			mini_export_hlpr(shell, argv, i, identifier);
		i++;
	}
}
