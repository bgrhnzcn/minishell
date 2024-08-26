/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:15:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/26 18:08:45 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_process(t_shell *shell, t_cmd *commands,
	int command_count, int i)
{
	commands[i + 1].pid = fork();
	if (commands[i + 1].pid == 0)
	{
		signal_cont(CHILD_P);
		close_pipes(shell->pipes, command_count, i);
		if (!commands[i + 1].fd_fail && i != command_count - 2)
			dup2(shell->pipes[i * 2 + 3], STDOUT_FILENO);
		if (!commands[i + 1].fd_fail && i != -1)
			dup2(shell->pipes[i * 2], STDIN_FILENO);
		if (!commands[i + 1].fd_fail && commands[i + 1].argv[0] != NULL
			&& !ft_strequ(commands[i + 1].argv[0], ""))
		{
			if (!apply_redirs(&commands[i + 1]))
				if (buildins(shell, &commands[i + 1]))
					executer(shell, commands[i + 1].argv);
		}
		free_cmds(commands, command_count);
		clear_pipes(shell->pipes, command_count);
		exit(g_global_exit);
	}
}

static t_bool	call_pipe(t_shell *shell, t_cmd *commands,
	int command_count)
{
	int	i;

	g_global_exit = 0;
	i = -1;
	while (i < command_count - 1)
	{
		g_global_exit = 0;
		get_redirs(&commands[i + 1]);
		i++;
	}
	i = -1;
	while (i < command_count - 1)
	{
		run_process(shell, commands, command_count, i);
		i++;
	}
	clear_pipes(shell->pipes, command_count);
	wait_all_childs(commands, command_count);
	return (EXIT_SUCCESS);
}

t_bool	pipe_check(t_shell *shell, t_token *token_list)
{
	t_cmd	*commands;
	int		command_count;

	command_count = get_command_count(token_list);
	commands = create_commands(command_count, token_list);
	if (commands == NULL)
		return (EXIT_FAILURE);
	if (command_count == 1)
	{
		if (single_command(shell, commands) == EXIT_FAILURE)
			return (free_cmds(commands, command_count), EXIT_FAILURE);
	}
	else
	{
		create_pipes(&shell->pipes, command_count);
		if (call_pipe(shell, commands, command_count))
			return (free_cmds(commands, command_count), EXIT_FAILURE);
	}
	free_cmds(commands, command_count);
	commands = NULL;
	return (EXIT_SUCCESS);
}
