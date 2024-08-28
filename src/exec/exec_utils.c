/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:31:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/28 16:07:02 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->redir_list)
		clear_tokens(cmd->redir_list);
	if (cmd->argv)
		ft_free_str_arr(cmd->argv);
	free(cmd);
}

void	wait_all_childs(t_cmd *commands, int command_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < command_count)
	{
		waitpid(commands[i].pid, &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		g_global_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global_exit = 128 + WTERMSIG(status);
}

void	free_cmds(t_cmd *commands, int command_count)
{
	int	i;

	i = 0;
	while (i < command_count)
	{
		if (commands[i].redir_list)
			clear_tokens(commands[i].redir_list);
		if (commands[i].argv)
			ft_free_str_arr(commands[i].argv);
		i++;
	}
	free(commands);
}

char	**split_path(t_shell *shell)
{
	char	**paths;
	char	*cmd;

	cmd = get_env(shell->env, "PATH");
	if (ft_strequ(cmd, ""))
		return (free(cmd), NULL);
	paths = ft_split(cmd, ':');
	if (paths == NULL)
		return (free(cmd), NULL);
	free(cmd);
	return (paths);
}

void	print_error(char *cmd, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(err), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
