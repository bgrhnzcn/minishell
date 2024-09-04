/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/02 12:50:41 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global_exit = 0;

static t_bool	main_exec(t_shell *shell)
{
	if (pipe_check(shell, &shell->token_list))
	{
		clear_tokens(shell->token_list.next);
		shell->token_list.next = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static t_bool	main_parse(t_shell *shell)
{
	if (parse(shell))
	{
		clear_tokens(shell->token_list.next);
		shell->token_list.next = NULL;
		shell->status = 2;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	init_shell(&shell, envp);
	while (true)
	{
		if (shell.input != NULL)
			free(shell.input);
		shell.input = get_input(&shell);
		if (ft_strequ(shell.input, ""))
			continue ;
		signal_cont(AFTER_IN_P);
		add_history(shell.input);
		if (main_parse(&shell))
			continue ;
		if (main_exec(&shell))
			continue ;
		clear_tokens(shell.token_list.next);
		shell.token_list.next = NULL;
	}
	free(shell.input);
	return (EXIT_SUCCESS);
}
