/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:31:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/02 12:44:50 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cmd_and_temp(t_shell *shell, char **cmd, char **temp, char **argv)
{
	if (ft_strchr(argv[0], '/') == argv[0])
	{
		*cmd = ft_strdup("");
		*temp = ft_strdup("");
	}
	else
	{
		*cmd = get_env(shell->env, "PWD");
		if (ft_strequ(*cmd, ""))
		{
			free(*cmd);
			*cmd = getcwd(NULL, 0);
			*temp = ft_strjoin(*cmd, "/");
		}
		else
			*temp = ft_strjoin(*cmd + 4, "/");
	}
}

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
	if (cmd[5] == 0)
		return (free(cmd), NULL);
	paths = ft_split(cmd + 5, ':');
	if (paths == NULL)
		return (free(cmd), NULL);
	free(cmd);
	return (paths);
}
