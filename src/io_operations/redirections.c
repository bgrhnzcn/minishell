/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/26 13:11:17 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	found_input(t_shell *shell, t_token *temp)
{
	if (shell->fdin != -1)
		close (shell->fdin);
	if (temp->type == HEREDOC)
		shell->fdin = open(temp->next->text, O_RDONLY, 0644);
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
		shell->fdout = open(temp->next->text, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (temp->type == OUTPUT)
		shell->fdout = open(temp->next->text, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->fdout == -1)
		perror("output error");
	dup2(shell->fdout, STDOUT_FILENO);
}

void	apply_redirs(t_shell *shell, t_token *command)
{
	t_token	*temp;
	t_token	*temp2;

	temp = command;
	while (temp != NULL)
	{
		if ((temp->type == INPUT || temp->type == HEREDOC)
			|| (temp->type == OUTPUT || temp->type == APPEND))
		{
			if (temp->type == INPUT || temp->type == HEREDOC)
				found_input(shell, temp);
			if (temp->type == OUTPUT || temp->type == APPEND)
				found_output(shell, temp);
			temp2 = temp->next->next;
			remove_token(command, temp->next);
			remove_token(command, temp);
			temp = temp2;
			continue ;
		}
		temp = temp->next;
	}
}

void	clear_redirs(t_shell *shell)
{
	shell->fdin = STDIN_FILENO;
	shell->fdout = STDOUT_FILENO;
}