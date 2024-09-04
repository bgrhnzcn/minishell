/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:16:49 by buozcan           #+#    #+#             */
/*   Updated: 2024/09/02 13:02:25 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(err), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	is_dir(char *cmd, char *argv)
{
	struct stat	path_stat;

	path_stat = (struct stat){0};
	if (!stat(cmd, &path_stat))
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(argv, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("Is a directory", STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			g_global_exit = 126;
			return (true);
		}
		else
			return (false);
	}
	return (false);
}
