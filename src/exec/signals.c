#include "minishell.h"


static void	ft_main_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_exit = 1;
	}
}
static void	ft_heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_global_exit = 999;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_on_new_line();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	signal_cont(t_shell *shell, int status)
{
	if (status == MAIN_P && !shell->is_heredoc_open)
	{
		signal(SIGINT, &ft_main_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == CHILD_P && !shell->is_heredoc_open)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == HEREDOC_P)
	{
		signal(SIGINT, &ft_heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
}
