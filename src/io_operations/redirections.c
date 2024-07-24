/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/24 15:48:36 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	found_input(t_shell *shell, t_token *temp)
{
	if (shell->fdin != -1)
		close (shell->fdin);
	if (temp->type == HEREDOC)
	{
		if (temp->next)
			shell->fdin = open(temp->next->next, O_RDONLY, 0644);
	}
	else if (temp->type == INPUT)
		shell->fdin = open(temp->next->text, O_RDONLY, 0644);
	if (shell->fdin == -1)
		perror ("input error");
    dup2(shell->fdin, STDIN_FILENO);
}

static void	found_output(t_shell *shell, t_token *temp)
{
	if (shell->fdout != -1)
		close(shell->fdout);
	if (temp->type == APPEND)
	{
		if (temp->next)
			shell->fdout = open(temp->next->text, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (temp->type == OUTPUT)
		shell->fdout = open(temp->next->text, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->fdout == -1)
		perror("output error");
	dup2(shell->fdout, STDOUT_FILENO);
}

void	apply_redirs(t_shell *shell, t_token *command)
{
	t_token	*temp;

	temp = command;
	while (temp != NULL)
	{
		if (temp->type == INPUT || temp->type == HEREDOC)
		{
			found_input(shell, temp);
			remove_token(command, temp->next);
			remove_token(command, temp);
		}
		if (temp->type == OUTPUT || temp->type == APPEND)
		{
			found_output(shell, temp);
			remove_token(command, temp->next);
			remove_token(command, temp);
		}
		temp = temp->next;
	}
}

void	clear_redirs(t_shell *shell)
{
	shell->fdin = STDIN_FILENO;
	shell->fdout = STDOUT_FILENO;
}