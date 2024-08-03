/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:37:58 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/03 22:58:54 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_command_count(t_token *token_list)
{
	t_token	*temp;
	int		command_count;

	temp = token_list;
	command_count = 1;
	while (temp != NULL)
	{
		if (temp->type == PIPE)
			command_count++;
		temp = temp->next;
	}
	return (command_count);
}

static void	clear_splitted(t_token **splitted, int command_count)
{
	int	i;

	i = 0;
	while (i < command_count)
	{
		clear_tokens(splitted[i]);
		i++;
	}
	free(splitted);
}

static t_token	**split_commands(int command_count, t_token *token_list)
{
	t_token	**splitted;
	t_token	*temp;
	t_token	*start;
	int		i;

	splitted = ft_calloc(command_count, sizeof(t_token *));
	if (splitted == NULL)
		return (NULL);
	i = 0;
	temp = token_list->next;
	start = temp;
	while (temp != NULL && i < command_count)
	{
		if (temp->type == TAIL || temp->type == PIPE)
		{
			splitted[i] = remove_sublist(start, temp->prev);
			if (splitted[i] == NULL)
				return (clear_splitted(splitted, i), NULL);
			i++;
			if (temp->type == PIPE)
				start = temp->next;
		}
		temp = temp->next;
	}
	return (splitted);
}

/*
void	print_command(t_cmd *command, int i)
{
	int	j;

	printf("command %d:\n", i);
	printf("fdin: %d\n", command->fdin);
	printf("fdout: %d\n", command->fdout);
	printf("fd_fail: %d\n", command->fd_fail);
	j = 0;
	while (command->argv[j] != NULL)
	{
		printf("argv[%d]: %s\n", j, command->argv[j]);
		j++;
	}
}

void	print_commands(t_cmd *commands, int command_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < command_count)
	{
		print_command(&commands[i], i);
		i++;
	}
}
*/

t_cmd	*create_commands(int command_count, t_token *token_list)
{
	t_cmd	*commands;
	t_token	**splitted;
	int		i;

	commands = ft_calloc(command_count, sizeof(t_cmd));
	if (commands == NULL)
		return (NULL);
	splitted = split_commands(command_count, token_list);
	if (splitted == NULL)
		return (free(commands), NULL);
	i = 0;
	while (i < command_count)
	{
		commands[i].fdin = -1;
		commands[i].fdout = -1;
		commands[i].fd_fail = false;
		if (get_redirs(&commands[i], splitted[i]))
			return (free(commands),
				clear_splitted(splitted, command_count),
				NULL);
		commands[i].argv = create_argv(splitted[i]);
		i++;
	}
	clear_splitted(splitted, command_count);
	return (commands);
}
