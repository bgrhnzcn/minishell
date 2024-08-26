/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/26 18:22:19 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	found_input(t_cmd *cmd, t_token *temp)
{
	if (cmd->fdin != -1 || cmd->heredoc_pipe[0] != -1)
	{
		if (cmd->fdin != -1)
		{
			close(cmd->fdin);
			cmd->fdin = -1;
		}
		if (cmd->heredoc_pipe[0] != -1 && temp->next->type == TAIL)
		{
			close(cmd->heredoc_pipe[0]);
			cmd->heredoc_pipe[0] = -1;
		}
	}
	cmd->fdin = open(temp->text + 1, O_RDONLY, 0644);
	if (cmd->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(temp->text + 1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_global_exit = 1;
		cmd->fd_fail = true;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static t_bool	found_output(t_cmd *cmd, t_token *temp)
{
	if (cmd->fdout != -1)
		close(cmd->fdout);
	if (temp->type == APPEND)
		cmd->fdout = open(temp->text + 2,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (temp->type == OUTPUT)
		cmd->fdout = open(temp->text + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (temp->type == APPEND)
			ft_putstr_fd(temp->text + 2, STDERR_FILENO);
		else
			ft_putstr_fd(temp->text + 1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_global_exit = 1;
		cmd->fd_fail = true;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_bool	apply_redirs(t_cmd *cmd)
{
	if (cmd->fd_fail == true)
	{
		if (cmd->fdin != -1)
			close(cmd->fdin);
		if (cmd->fdout != -1)
			close(cmd->fdout);
		return (EXIT_FAILURE);
	}
	if (cmd->fdin != -1 || cmd->heredoc_pipe[0] != -1)
	{
		if (cmd->fdin == -1)
			cmd->fdin = cmd->heredoc_pipe[0];
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(cmd->fdin);
	}
	if (cmd->fdout != -1)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
	return (EXIT_SUCCESS);
}

t_bool	get_redirs(t_cmd *cmd)
{
	t_token	*temp;
	t_bool	status;

	temp = cmd->redir_list;
	status = EXIT_SUCCESS;
	get_heredoc(cmd);
	while (temp != NULL)
	{
		if (temp->type == OUTPUT || temp->type == APPEND)
			status = found_output(cmd, temp);
		if (temp->type == INPUT)
			status = found_input(cmd, temp);
		if (status == EXIT_FAILURE)
			return (cmd->fd_fail = true, EXIT_FAILURE);
		temp = temp->next;
	}
	if (cmd->heredoc_pipe[0] != -1)
	{
		if (cmd->fdin != -1)
			close(cmd->fdin);
		cmd->fdin = cmd->heredoc_pipe[0];
	}
	return (EXIT_SUCCESS);
}
