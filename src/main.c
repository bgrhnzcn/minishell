/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/26 18:27:54 by bgrhnzcn         ###   ########.fr       */
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
	shell->input = malloc(0);
	shell->token_list.type = HEAD;
	shell->token_list.text = "";
	shell->token_list.prev = NULL;
	shell->token_list.next = NULL;
	shell->fdout = STDOUT_FILENO;
	shell->fdin = STDIN_FILENO;
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

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*input_trimmed;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	init_shell(&shell, envp);
	while (true)
	{
		free(shell.input);
		shell.input = get_input(&shell);
		add_history(shell.input);
		input_trimmed = ft_strtrim(shell.input, g_whitespaces);
		if (parse_input(&shell.token_list, input_trimmed))
		{
			free(input_trimmed);
			clear_tokens(&shell.token_list);
			continue ;
		}
		free(input_trimmed);
		if (check_quotes(&shell.token_list))
		{
			clear_tokens(&shell.token_list);
			continue ;
		}
		if (check_syntax(&shell.token_list, shell.env) == error)
		{
			clear_tokens(&shell.token_list);
			continue ;
		}
		perform_expansion(&shell.token_list, shell.env);
		join_cont_words(&shell.token_list);
		remove_whitespaces(&shell.token_list);
		pipe_check(&shell, &shell.token_list);
		clear_tokens(&shell.token_list);
	}
	free(shell.input);
	return (EXIT_SUCCESS);
}
