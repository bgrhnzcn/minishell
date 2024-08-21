/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/20 17:58:21 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*cwd;

	cwd = NULL;
	prompt = ft_calloc(300, sizeof(char));
	ft_strlcat(prompt, ANSI_COLOR_GREEN"minishell"ANSI_COLOR_RESET, 300);
	ft_strlcat(prompt, "@", 300);
	cwd = get_env(shell->env, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		ft_strlcat(prompt, ANSI_COLOR_BLUE, 300);
		ft_strlcat(prompt, ft_strrchr(cwd, '/') + 1, 300);
		ft_strlcat(prompt, ANSI_COLOR_RESET, 300);
		ft_strlcat(prompt, "> ", 300);
		free(cwd);
		return (prompt);
	}
	ft_strlcat(prompt, ANSI_COLOR_BLUE, 300);
	ft_strlcat(prompt, ft_strrchr(cwd, '/') + 1, 300);
	ft_strlcat(prompt, ANSI_COLOR_RESET, 300);
	ft_strlcat(prompt, "> ", 300);
	free(cwd);
	return (prompt);
}

void	init_shell(t_shell *shell, char **envp)
{
	if (init_env(shell, envp))
	{
		printf("Error: initialization of env is failed.\n");
		exit(EXIT_FAILURE);
	}
	shell->input = malloc(1);
	shell->token_list.type = HEAD;
	shell->token_list.text = "";
	shell->token_list.prev = NULL;
	shell->token_list.next = NULL;
}

char	*get_input(t_shell *shell)
{
	char	*input;
	char	*prompt;

	prompt = create_prompt(shell);
	printf(ANSI_COLOR_RED"readline_v: %s "ANSI_COLOR_RESET, rl_library_version);
	input = readline(prompt);
	free(prompt);
	return (input);
}

t_bool	parse(t_shell *shell)
{
	char	*input_trimmed;

	input_trimmed = ft_strtrim(shell->input, g_whitespaces);
	if (parse_input(&shell->token_list, input_trimmed, shell->status))
		return (free(input_trimmed),
			clear_tokens(shell->token_list.next),
			shell->token_list.next = NULL, EXIT_FAILURE);
	free(input_trimmed);
	if (check_quotes(&shell->token_list))
		return (clear_tokens(shell->token_list.next),
			shell->token_list.next = NULL, EXIT_FAILURE);
	if (check_syntax(&shell->token_list, shell->env))
		return (clear_tokens(shell->token_list.next),
			shell->token_list.next = NULL, EXIT_FAILURE);
	perform_expansion(&shell->token_list, shell->env);
	join_cont_words(&shell->token_list);
	remove_whitespaces(&shell->token_list);
	merge_redirs(&shell->token_list);
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
		add_history(shell.input);
		if (parse(&shell))
		{
			clear_tokens(shell.token_list.next);
			shell.token_list.next = NULL;
			shell.status = 2;
			continue ;
		}
		if (pipe_check(&shell, &shell.token_list))
		{
			clear_tokens(shell.token_list.next);
			shell.token_list.next = NULL;
			continue ;
		}
		clear_tokens(shell.token_list.next);
		shell.token_list.next = NULL;
	}
	free(shell.input);
	return (EXIT_SUCCESS);
}
