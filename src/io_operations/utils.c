/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:31:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/05 15:00:18 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd->argv)
		ft_free_str_arr(cmd->argv);
	free(cmd);
}

void	save_std_io(t_shell *shell)
{
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
}

void	restore_std_io(t_shell *shell)
{
	dup2(shell->saved_stdin, STDIN_FILENO);
	dup2(shell->saved_stdout, STDOUT_FILENO);
}

void	wait_all_childs(void)
{
	pid_t	wpid;

	while (true)
	{
		wpid = wait(NULL);
		if (wpid == -1)
			break ;
	}
}
