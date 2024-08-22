/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:08:54 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/22 14:50:42 by olyetisk         ###   ########.fr       */
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
	return (1);
}

static	char	*get_identifier(const char *arg)
{
	char	*equals_check;
	char	*identifier;

	equals_check = strchr(arg, '=');
	if (!equals_check)
		return (NULL);
	identifier = strndup(arg, equals_check - arg);
	if (!identifier || !valid_identifier(identifier))
	{
		free(identifier);
		return (NULL);
	}
	return (identifier);
}

void	mini_export(t_shell *shell, char **argv)
{
	int		i;
	char	*identifier;

	i = 1;
	while (argv[i])
	{
		identifier = get_identifier(argv[i]);
		if (!identifier)
		{
			printf("export: not an identifier: %s\n", argv[i]);
			i++;
			continue ;
		}
		if (!check_env(shell, identifier, argv[i]))
		{
			if (!add_new_env(shell, argv[i]))
			{
				free (identifier);
				return ;
			}
		}
		free (identifier);
		i++;
	}
}
