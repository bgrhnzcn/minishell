/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:13:02 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/29 12:45:46 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(t_str_vec *env, char *path)
{
	char	*home;
	char	*temp;

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
	temp = get_env(*env, "PWD");
	if (temp == NULL)
	{
		temp = getcwd(NULL, 0);
		set_env(env, "OLDPWD", temp);
		free(temp);
	}
	set_env(env, "OLDPWD", temp + 4);
	set_env(env, "PWD", home + 5);
}

static void	cd_abs_path(t_str_vec *env, char *path)
{
	char	*temp;

	if (chdir(path))
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return ;
	}
	temp = get_env(*env, "PWD");
	if (temp == NULL)
	{
		temp = getcwd(NULL, 0);
		set_env(env, "OLDPWD", temp);
		free(temp);
	}
	set_env(env, "OLDPWD", temp + 4);
	set_env(env, "PWD", path);
}

static void	cd_rel_path(t_str_vec *env, char *path)
{
	char	*temp;

	if (chdir(path))
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return ;
	}
	temp = get_env(*env, "PWD");
	if (temp == NULL)
	{
		temp = getcwd(NULL, 0);
		set_env(env, "OLDPWD", temp);
		free(temp);
	}
	set_env(env, "OLDPWD", temp + 4);
	set_env(env, "PWD", path);
}

void	cd(t_str_vec *env, char *path)
{
	char	*home;
	char	*temp;

	//default path
	if (path == NULL)
		cd_home(env, path);
	//absolute path
	else if (path[0] == '/')
		cd_abs_path(env, path);
	else
		cd_rel_path(env, path);
}
