/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:51:34 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/01 18:56:25 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_exit_code(int status)
{
	if (WIFEXITED(status))
	{
		g_global_exit = WEXITSTATUS(status);
		return (EXIT_SUCCESS);
	}
	else if (WIFSIGNALED(status))
	{
		g_global_exit = 128 + WTERMSIG(status);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void	ft_main_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_exit = 999;
	}
}

static void	ft_main_after_in_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		g_global_exit = 999;
	}
}

static void	ft_heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_global_exit = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_cont(int status)
{
	if (status == MAIN_P)
	{
		signal(SIGINT, &ft_main_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == CHILD_P)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == HEREDOC_P)
	{
		signal(SIGINT, &ft_heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == AFTER_IN_P)
	{
		signal(SIGINT, &ft_main_after_in_signal);
		signal(SIGQUIT, SIG_IGN);
	}
}
