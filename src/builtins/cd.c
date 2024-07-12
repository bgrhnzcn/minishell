/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:13:02 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/12 12:25:53 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(char **env)
{
	char	*home;
	char	*pwd;

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
	pwd = get_env(env, "PWD");
	set_env(env, "OLDPWD", (pwd + 4));
	set_env(env, "PWD", home + 5);
	free(home);
	free(pwd);
}

static void	cd_abs_path(char ** env, char *path)
{
	char	*temp;
	char	*pwd;

	if (chdir(path))
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return ;
	}
	pwd = get_env(env, "PWD");
	set_env(env, "OLDPWD", pwd + 4);
	temp = getcwd(NULL, 0);
	set_env(env, "PWD", temp);
	free(pwd);
	free(temp);
}

static void	cd_rel_path(char ** env, char *path)
{
	char	*temp;
	char	*pwd;

	if (chdir(path))
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return ;
	}
	pwd = get_env(env, "PWD");
	set_env(env, "OLDPWD", pwd + 4);
	temp = getcwd(NULL, 0);
	set_env(env, "PWD", temp);
	free(pwd);
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
