/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:15:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/19 17:27:24 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mini_pipe(t_token **commands, int command_count, int *pipes[2])
{
	(void)command_count;
	(void)commands;
	(void)pipes;
}

t_bool	pipe_check(t_shell *shell, t_token *token_list)
{
	t_token	**commands;
	int		command_count;
	int		p[2];
	int		pid;

	command_count = get_command_count(token_list);
	if (command_count == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			apply_redirs(shell, token_list);
			executer(shell, create_argv(token_list->next));
			clear_redirs(shell);
			exit(127);
		}
	}
	if (pipe(p) == -1)
	{
		perror("pipe cant open\n");
		exit(127);
	}
	pid = fork();
	if (pid == 0)
	{
		
	}
	commands = ft_calloc(command_count, sizeof (t_token *));
	if (commands == NULL)
		return (UNIMPLEMENTED("pipe.c - malloc\n"), error);
	if (create_commands(commands, command_count, token_list) == error)
		return (UNIMPLEMENTED("pipe.c - commands\n"), error);
	mini_pipe(commands, command_count, p);
	return (UNIMPLEMENTED("pipe.c - run\n"), true);
}

static void	pipe_exec(char **run, t_cmds *temp, int i)
{
	int		p[2];

	pipecheck(p);
	temp->pid = fork();
	if (temp->pid == 0)
	{
		set_signal(CHILD_P);
		close(p[0]);
		set_input(temp, i);
		set_output(temp, p, i);
		close(p[1]);
		check_built_f(temp);
		builtornot(temp, run);
	}
	close(p[1]);
	dup2(p[0], 0);
	close(p[0]);
}