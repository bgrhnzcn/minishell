/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/03 23:23:12 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc(t_cmd *cmd, t_token *temp)
{
	char	*delimiter;
	char	*line;
	char	*temp_file = ft_strdup("/tmp/.here_doc");
	int		temp_fd;

	delimiter = temp->next->text;
	temp_fd = open(temp_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (temp_fd < 0)
	{
		perror("Error opening temporary file");
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strequ(line, delimiter))
		{
			free(line);
			ft_putstr_fd("\n", temp_fd);
			break ;
		}
		ft_putstr_fd(line, temp_fd);
		free(line);
	}
	close(temp_fd);
	cmd->fdin = open(temp_file, O_RDONLY);
	if (cmd->fdin == -1)
		perror("input error");
}

static t_bool	found_input(t_cmd *cmd, t_token *temp)
{
	if (cmd->fdin != -1)
		close(cmd->fdin);
	if (temp->type == HEREDOC)
		handle_heredoc(cmd, temp);
	else if (temp->type == INPUT)
		cmd->fdin = open(temp->next->text, O_RDONLY, 0644);
	if (cmd->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(temp->next->text, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
		cmd->fdout = open(temp->next->text,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (temp->type == OUTPUT)
		cmd->fdout = open(temp->next->text, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(temp->next->text, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
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
	if (cmd->fdin != -1)
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		close(cmd->fdin);
	}
	if (cmd->fdout != -1)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
	return (EXIT_SUCCESS);
}

t_bool	get_redirs(t_cmd *cmd, t_token *command)
{
	t_token	*temp;
	t_token	*temp2;
	t_bool	status;

	temp = command;
	while (temp != NULL)
	{
		if ((temp->type == INPUT || temp->type == HEREDOC)
			|| (temp->type == OUTPUT || temp->type == APPEND))
		{
			if (temp->type == INPUT || temp->type == HEREDOC)
				status = found_input(cmd, temp);
			if (temp->type == OUTPUT || temp->type == APPEND)
				status = found_output(cmd, temp);
			temp2 = temp->next->next;
			remove_token(command, temp->next);
			remove_token(command, temp);
			temp = temp2;
			if (status == EXIT_FAILURE)
				return (EXIT_FAILURE);
			continue ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
