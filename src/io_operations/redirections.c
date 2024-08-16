/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:05:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/16 19:26:47 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(const char *delimiter, const char *temp_file_path) {
    char *line;
    int temp_fd;
    pid_t pid;

	temp_fd = open(temp_file_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (temp_fd < 0)
	{
		perror("Error opening temporary file");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		close(temp_fd);
		return ;
	}
	else if (pid == 0)
	{
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = (char *)malloc(1024);
			if (!line)
			{
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
			size_t bytes_read = read(STDIN_FILENO, line, 1024);
			if (bytes_read < 0)
			{
				perror("Error reading line");
				free(line);
				exit(EXIT_FAILURE);
			}
			if (line[bytes_read - 1] == '\n')
				line[bytes_read - 1] = '\0';
			if (strcmp(line, delimiter) == 0)
			{

				free(line);
				break;
			}
			write(temp_fd, line, strlen(line));
			write(temp_fd, "\n", 1); 
			free(line);
		}
		close(temp_fd); 
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
		temp_fd = open(temp_file_path, O_RDONLY);
		if (temp_fd == -1)
		{
			perror("Error reopening temporary file");
			return;
		}
		if (dup2(temp_fd, STDIN_FILENO) == -1)
			perror("Error redirecting stdin");
		close(temp_fd); 
	}
}

static t_bool	found_input(t_cmd *cmd, t_token *temp)
{
	char *temp_file = ft_strdup("/tmp/.here_doc");
	if (cmd->fdin != -1)
		close(cmd->fdin);
	if (temp->type == HEREDOC)
	{
		handle_heredoc(temp->text + 2, temp_file);
		cmd->fdin = open(temp_file, O_RDONLY, 0644);
	}
	else if (temp->type == INPUT)
		cmd->fdin = open(temp->text + 1, O_RDONLY, 0644);
	if (cmd->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (temp->type == HEREDOC)
			ft_putstr_fd(temp->text + 2, STDERR_FILENO);
		else
			ft_putstr_fd(temp->text + 1, STDERR_FILENO);
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

t_bool	get_redirs(t_cmd *cmd)
{
	t_token	*temp;
	t_bool	status;

	temp = cmd->redir_list;
	while (temp != NULL)
	{
		if ((temp->type == INPUT || temp->type == HEREDOC)
			|| (temp->type == OUTPUT || temp->type == APPEND))
		{
			if (temp->type == INPUT || temp->type == HEREDOC)
				status = found_input(cmd, temp);
			if (temp->type == OUTPUT || temp->type == APPEND)
				status = found_output(cmd, temp);
			if (status == EXIT_FAILURE)
			{
				cmd->fd_fail = true;
				return (EXIT_FAILURE);
			}
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
