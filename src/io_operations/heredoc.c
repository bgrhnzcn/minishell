/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:04:00 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/20 16:08:47 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_hlpr(t_cmd *cmd, const char *delimiter)
{
	char	*line;

	close(cmd->heredoc_pipe[0]);
	while (1)
	{
		line = readline("> ");
		if (ft_strequ(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, cmd->heredoc_pipe[1]);
		free(line);
	}
	close(cmd->heredoc_pipe[1]);
	exit(EXIT_SUCCESS);
}

static void	handle_heredoc(const char *delimiter, t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->heredoc_pipe[0] != -1)
	{
		close(cmd->heredoc_pipe[0]);
		cmd->heredoc_pipe[0] = -1;
	}
	if (pipe(cmd->heredoc_pipe))
	{
		ft_putendl_fd("minishell: pipe failed", STDERR_FILENO);
		return ;
	}
	pid = fork();
	if (pid == 0)
		handle_heredoc_hlpr(cmd, delimiter);
	else
	{
		waitpid(pid, NULL, 0);
		close(cmd->heredoc_pipe[1]);
	}
}

void	get_heredoc(t_cmd *cmd)
{
	t_token	*temp;

	temp = cmd->redir_list;
	while (temp != NULL)
	{
		if (temp->type == HEREDOC)
			handle_heredoc(temp->text + 2, cmd);
		temp = temp->next;
	}
}
