/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:19:21 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/20 16:20:19 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_std_io(t_shell *shell)
{
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
}

void	restore_std_io(t_shell *shell)
{
	dup2(shell->saved_stdin, STDIN_FILENO);
	dup2(shell->saved_stdout, STDOUT_FILENO);
}

void	close_pipes(int *pipes, int command_count, int not_close)
{
	int	i;

	i = -1;
	while (i < command_count - 1)
	{
		if (i != not_close)
		{
			if (i != -1)
			{
				close(pipes[i * 2]);
				pipes[i * 2] = -1;
			}
			if (i != command_count - 2)
			{
				close(pipes[i * 2 + 3]);
				pipes[i * 2 + 3] = -1;
			}
		}
		i++;
	}
}

void	clear_pipes(int *pipes, int command_count)
{
	int	i;

	i = 0;
	while (i < command_count - 1)
	{
		close(pipes[i * 2]);
		close(pipes[i * 2 + 1]);
		i++;
	}
	free(pipes);
}

void	create_pipes(int **p, int command_count)
{
	int	i;

	*p = malloc(sizeof (int) * (command_count - 1) * 2);
	if (p == NULL)
		return ;
	i = 0;
	while (i < command_count - 1)
	{
		pipe(*p + i * 2);
		i++;
	}
}
