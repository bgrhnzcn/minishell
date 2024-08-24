/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:04:00 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/24 15:59:37 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_hlpr(t_cmd *cmd, const char *delimiter)
{
	char	*line;

	close(cmd->heredoc_pipe[0]);
	while (1)
	{
		signal_cont(HEREDOC_P);
		line = readline("> ");
		if (g_global_exit == 999)
			exit(2);
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

static void	handle_heredoc(const char *delimiter, t_cmd *cmd, int *status)
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
		waitpid(pid, status, 0);
		close(cmd->heredoc_pipe[1]);
	}
}

int	get_heredoc(t_cmd *cmd)
{
	t_token	*temp;
	int		status;

	temp = cmd->redir_list;
	status = 0;
	while (temp != NULL)
	{
		if (temp->type == HEREDOC)
			handle_heredoc(temp->text + 2, cmd, &status);
		if (status >> 8 == 2)
			return(EXIT_FAILURE);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
