/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:15:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/28 14:26:18 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_std_io(t_shell *shell)
{
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);	
}

static void	restore_std_io(t_shell *shell)
{
	dup2(shell->saved_stdin, STDIN_FILENO);
	dup2(shell->saved_stdout, STDOUT_FILENO);
}

t_bool	single_command(t_shell *shell, t_token *token_list)
{
	char	**argv;
	int		status;

	save_std_io(shell);
	apply_redirs(shell, token_list);
	argv = create_argv(token_list->next);
	if (!buildins(shell, argv))
		return (restore_std_io(shell), status = 0, true);
	shell->pid = fork();
	if (shell->pid == 0)
	{
		executer(shell, argv);
		exit(127);
	}
	restore_std_io(shell);
	waitpid(shell->pid, &status, 0);
	return (true);
}

t_bool	pipe_check(t_shell *shell, t_token *token_list)
{
	t_token	**commands;
	int		command_count;
	int		i;
	int		p[2];
	int		status;

	command_count = get_command_count(token_list);
	if (command_count == 1)
		single_command(shell, token_list);
	else
	{
		commands = create_commands(command_count, token_list);
		if (commands == NULL)
			return (error);
		i = 0;
		save_std_io(shell);
		while (i < command_count - 1)
		{
			if (pipe(p) == -1)
			{
				perror("pipe cant open\n");
				exit(127);
			}
			shell->pid = fork();
			if (shell->pid == 0)
			{
				close(p[0]);
				dup2(p[1], STDOUT_FILENO);
				close(p[1]);
				apply_redirs(shell, commands[i]);
				executer(shell, create_argv(commands[i]->next));
				exit(127);
			}
			close(p[1]);
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			i++;
		}
		shell->pid = fork();
		shell->fdout = shell->saved_stdout;
		if (shell->pid == 0)
		{
			apply_redirs(shell, commands[i]);
			executer(shell, create_argv(commands[i]->next));
			exit(127);
		}
		close(p[0]);
		close(p[1]);
		i = 0;
		while (i < command_count)
		{
			wait(&status);
			i++;
		}
		restore_std_io(shell);
		return (true);
	}
}
