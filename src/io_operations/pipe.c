/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:15:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/02 23:57:48 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(int *pipes, int command_count, int not_close)
{
	
}

static void	create_pipes(int **p, int command_count)
{
	int	i;

	*p = malloc(sizeof (int[2]) * (command_count - 1));
	if (p == NULL)
		return ;
	i = 0;
	while (i < command_count - 1)
	{
		pipe(p[i * 2]);
		i++;
	}
}

static void	call_pipe(t_shell *shell, t_cmd *commands, int command_count)
{
	int	i;
	int	*pipes;

	create_pipes(&pipes, command_count);
	i = -1;
	while (i < command_count - 1)
	{
		shell->pid = fork();
		if (shell->pid == 0)
		{
			if (i != command_count - 2)
				dup2(pipes[i * 2 + 3], STDOUT_FILENO);
			if (i != -1)
				dup2(pipes[i * 2], STDIN_FILENO);
			close_pipes(pipes, command_count, i);
			if (!apply_redirs(&commands[i]))
				executer(shell, commands[i].argv);
			free_cmd(&commands[i]);
			exit(127);
		}
		i++;
	}
}

t_bool	pipe_check(t_shell *shell, t_token *token_list)
{
	t_cmd	*commands;
	int		command_count;

	command_count = get_command_count(token_list);
	if (command_count == 1)
		single_command(shell, create_commands(command_count, token_list));
	else
	{
		commands = create_commands(command_count, token_list);
		call_pipe(shell, commands, command_count);
	}
}
