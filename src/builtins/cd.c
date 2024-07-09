/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:13:02 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/08 18:29:21 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(char **env)
{
	char	*home;

	home = get_env(env, "HOME");
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
	set_env(env, "OLDPWD", (get_env(env, "PWD") + 4));
	set_env(env, "PWD", home + 5);
}

static void	cd_abs_path(char ** env, char *path)
{
	char	*temp;

	if (chdir(path))
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return ;
	}
	set_env(env, "OLDPWD", (get_env(env, "PWD") + 4));
	temp = getcwd(NULL, 0);
	set_env(env, "PWD", temp);
	free(temp);
}

static void	cd_rel_path(char ** env, char *path)
{
	char	*temp;

	if (chdir(path))
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return ;
	}
	set_env(env, "OLDPWD", (get_env(env, "PWD") + 4));
	temp = getcwd(NULL, 0);
	set_env(env, "PWD", temp);
	free(temp);
}

void	mini_cd(char **env, char *path)
{
	//default path
	if (path == NULL)
		cd_home(env);
	//absolute path
	else if (path[0] == '/')
		cd_abs_path(env, path);
	else
		cd_rel_path(env, path);
}
