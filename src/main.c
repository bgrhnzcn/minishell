/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/21 01:58:38 by bgrhnzcn         ###   ########.fr       */
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
}

char	*get_input(t_shell *shell)
{
	char	*input;
	char	*prompt;

	prompt = create_prompt(shell);
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
		parse_input(&shell.token_list, input_trimmed);
		check_quotes(&shell.token_list);
		free(input_trimmed);
		if (check_syntax(&shell.token_list, shell.env) == error)
		{
			clear_tokens(&shell.token_list);
			continue ;
		}
		perform_expansion(&shell.token_list, shell.env);
		join_cont_words(&shell.token_list);
		remove_whitespaces(&shell.token_list);
		pipe_check(&shell, &shell.token_list);
		//shell.argv = create_argv(shell.token_list.next);
		//executer(&shell, shell.argv);
		clear_tokens(&shell.token_list);
	}
	free(shell.input);
	return (EXIT_SUCCESS);
}
