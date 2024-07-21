/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:37:58 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/21 14:44:28 by bgrhnzcn         ###   ########.fr       */
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

t_token	**create_commands(int command_count, t_token *token_list)
{
	t_token	**commands;
	t_token	*temp;
	t_token	*start;
	int		i;

	commands = ft_calloc(command_count, sizeof (t_token *));
	if (commands == NULL)
		return (NULL);
	temp = token_list->next;
	start = temp;
	i = 0;
	while (temp != NULL && i < command_count)
	{
		if (temp->type == TAIL || temp->type == PIPE)
		{
			commands[i] = remove_sublist(start, temp->prev);
			if (commands[i] == NULL)
				return (ft_free_str_arr(commands), NULL);
			i++;
			if (temp->type == PIPE)
				start = temp->next;
		}
		temp = temp->next;
	}
	return (commands);
}
