/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:15:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/16 22:29:14 by bgrhnzcn         ###   ########.fr       */
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
	int		**pipes;
	int		pid;

	command_count = get_command_count(token_list);
	if (command_count == 1)
	{
		apply_redirs(shell, token_list);
		return (executer(shell, create_argv(token_list->next)), true);
	}
	commands = ft_calloc(command_count, sizeof (t_token *));
	if (commands == NULL)
		return (UNIMPLEMENTED("pipe.c - malloc\n"), error);
	if (create_commands(commands, command_count, token_list) == error)
		return (UNIMPLEMENTED("pipe.c - commands\n"), error);
	pipes = ft_calloc(sizeof (int [2]), command_count - 1);
	if (pipes == NULL)
		return (UNIMPLEMENTED("pipe.c - malloc\n"), error);
	mini_pipe(commands, command_count, pipes);
	return (UNIMPLEMENTED("pipe.c - run\n"), true);
}
