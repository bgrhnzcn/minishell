/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/16 16:44:25 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirs(t_shell *shell, t_token *command)
{
	t_token	*temp;

	temp = command;
	while (temp != NULL)
	{
		if (temp->type == INPUT)
		{
			UNIMPLEMENTED("INPUT\n");
			remove_token(command, temp->next);
			remove_token(command, temp);
		}
		if (temp->type == OUTPUT)
		{
			UNIMPLEMENTED("OUTPUT\n");
			remove_token(command, temp->next);
			remove_token(command, temp);
		}
		if (temp->type == APPEND)
		{
			UNIMPLEMENTED("APPEND\n");
			remove_token(command, temp->next);
			remove_token(command, temp);
		}
		if (temp->type == HEREDOC)
		{
			remove_token(command, temp->next);
			remove_token(command, temp);
			UNIMPLEMENTED("HEREDOC\n");
		}
		temp = temp->next;
	}
}
