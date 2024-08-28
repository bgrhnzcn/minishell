/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:13:02 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/27 13:56:12 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(char **env)
{
	char	*home;
	char	*pwd;

	home = get_env(env, "HOME");
	if (ft_strequ(home, ""))
	{
		free(home);
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		g_global_exit = 1;
		return ;
	}
	pwd = get_env(env, "PWD");
	if (ft_strequ(pwd, ""))
		ft_get_cwd(&pwd);
	if (chdir(home + 5))
	{
		cd_print_error(home + 5, errno);
		free(pwd);
		free(home);
		g_global_exit = 1;
		return ;
	}
	free(home);
	cd_change_pwds(env, pwd);
}

static void	cd_path(char **env, char *path)
{
	char	*pwd;

	pwd = get_env(env, "PWD");
	if (ft_strequ(pwd, ""))
		ft_get_cwd(&pwd);
	if (chdir(path))
	{
		free(pwd);
		cd_print_error(path, errno);
		g_global_exit = 1;
		return ;
	}
	cd_change_pwds(env, pwd);
}

void	mini_cd(char **env, t_cmd *cmd)
{
	if (cmd->argv[1] == NULL)
		cd_home(env);
	else
		cd_path(env, cmd->argv[1]);
}
