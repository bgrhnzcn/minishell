/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:35:14 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/01 19:32:13 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_print_error(char *path, int err)
{
	ft_putstr_fd("minishell: cd:", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(err), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	cd_change_pwds(char **env, char *pwd)
{
	char	*curr;

	curr = getcwd(NULL, 0);
	set_env(env, "OLDPWD", pwd + 4);
	set_env(env, "PWD", curr);
	free(curr);
	free(pwd);
}

void	ft_get_cwd(char **pwd)
{
	free(*pwd);
	*pwd = getcwd(NULL, 0);
}
