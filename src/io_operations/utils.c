/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:31:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/06 23:41:24 by bgrhnzcn         ###   ########.fr       */
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

char	**split_path(t_shell *shell)
{
	char	**paths;
	char	*cmd;

	cmd = get_env(shell->env, "PATH");
	if (cmd == NULL)
		return (NULL);
	paths = ft_split(cmd, ':');
	if (paths == NULL)
		return (free(cmd), NULL);
	free(cmd);
	return (paths);
}
