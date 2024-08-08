/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:15:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/08 23:38:50 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int *pipes, int command_count, int not_close)
{
	int	i;

	i = -1;
	while (i < command_count - 1)
	{
		if (i != not_close)
		{
			if (i != -1)
			{
				close(pipes[i * 2]);
				pipes[i * 2] = -1;
			}
			if (i != command_count - 2)
			{
				close(pipes[i * 2 + 3]);
				pipes[i * 2 + 3] = -1;
			}
		}
		i++;
	}
}

static void	clear_pipes(int *pipes, int command_count)
{
	int	i;

	i = 0;
	while (i < command_count - 1)
	{
		close(pipes[i * 2]);
		close(pipes[i * 2 + 1]);
		i++;
	}
	free(pipes);
}

static void	create_pipes(int **p, int command_count)
{
	int	i;

	*p = malloc(sizeof (int) * (command_count - 1) * 2);
	if (p == NULL)
		return ;
	i = 0;
	while (i < command_count - 1)
	{
		pipe(*p + i * 2);
		i++;
	}
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

static void	call_pipe(t_shell *shell, t_cmd *commands,
	int command_count, int *pipes)
{
	int	i;

	i = -2;
	while (++i < command_count - 1)
	{
		shell->pid = fork();
		if (shell->pid == 0)
		{
			close_pipes(pipes, command_count, i);
			if (i != command_count - 2)
				dup2(pipes[i * 2 + 3], STDOUT_FILENO);
			if (i != -1)
				dup2(pipes[i * 2], STDIN_FILENO);
			if (!get_redirs(&commands[i + 1]) &&
				commands[i + 1].argv[0] != NULL &&
				!ft_strequ(commands[i + 1].argv[0], ""))
			{
				if (!apply_redirs(&commands[i + 1]))
					executer(shell, commands[i + 1].argv);
				printf("minishell: %s: command not found\n",
					commands[i + 1].argv[0]);
			}
			free_cmds(commands, command_count);
			clear_pipes(pipes, command_count);
			exit(127);
		}
	}
	clear_pipes(pipes, command_count);
	wait_all_childs();
}

t_bool	pipe_check(t_shell *shell, t_token *token_list)
{
	t_cmd	*commands;
	int		*pipes;
	int		command_count;

	command_count = get_command_count(token_list);
	commands = create_commands(command_count, token_list);
	if (commands == NULL)
		return (EXIT_FAILURE);
	if (command_count == 1)
		single_command(shell, commands);
	else
	{
		create_pipes(&pipes, command_count);
		call_pipe(shell, commands, command_count, pipes);
	}
	free_cmds(commands, command_count);
	commands = NULL;
	return (EXIT_SUCCESS);
}
