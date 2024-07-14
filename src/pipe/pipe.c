/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:15:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/14 14:23:34 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mini_pipe(t_token **commands, int command_count, int *pipes[2])
{
	(void)command_count;
	(void)commands;
	(void)pipes;
}

t_bool	pipe_check(t_token *token_list)
{
	t_token	**commands;
	int		command_count;
	int		*pipes[2];
	int		i;

	command_count = get_command_count(token_list);
	if (command_count == 1)
		return (UNIMPLEMENTED("pipe.c - not exist"), true);
	commands = ft_calloc(command_count, sizeof (t_token *));
	if (commands == NULL)
		return (UNIMPLEMENTED("pipe.c - malloc"), error);
	if (create_commands(commands, command_count, token_list))
		return (UNIMPLEMENTED("pipe.c - commands"), error);
	i = 0;
	while (i < command_count - 1)
	{
		pipes[i] = malloc(sizeof (int [2]));
	}
	mini_pipe(commands, command_count, pipes);
	return (UNIMPLEMENTED("pipe.c - run"), true);
}
