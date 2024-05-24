/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:13:02 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/24 17:16:00 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_str_vec *env, char *path)
{
	char	*home;

	//default path
	if (path == NULL)
	{
		home = get_env(*env, "HOME");
		if (home == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
		if (chdir(home + 5))
		{
			printf("minishell: cd: %s: %s\n", home, strerror(errno));
			return ;
		}
		set_env(env, "PWD", home);
	}
	//absolute path
	else if (path[0] == '/')
	{
		if (chdir(path))
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
	}
	else if (chdir(path))
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
}
