/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/30 17:55:05 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*cwd;

	cwd = NULL;
	prompt = malloc(sizeof(char) * 200);
	ft_strlcat(prompt, "minishell@", 200);
	cwd = get_env(shell->env, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		ft_strlcat(prompt, cwd, 200);
		ft_strlcat(prompt, " > ", 200);
		free(cwd);
	}
	else
	{
		ft_strlcat(prompt, cwd + 4, 200);
		ft_strlcat(prompt, "> ", 200);
	}
	return (prompt);
}

void	init_shell(t_shell *shell, char **envp)
{
	init_env(shell, envp);
	shell->input = malloc(0);
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

int	buildins(t_shell *shell, char **argv)
{
	if (ft_strnstr(argv[0], "env", 4))
		mini_env(shell->env);
	else if (ft_strnstr(argv[0], "pwd", 4))
		mini_pwd(shell->env);
	else if (ft_strnstr(argv[0], "cd", 3))
		mini_cd(shell->env, argv[1]);
	else if (ft_strnstr(argv[0], "export", 7))
		mini_export(shell, "Deneme");
	else if (ft_strnstr(argv[0], "unset", 6))
		mini_unset(shell, "Deneme");
	else
		return (1);
	return (0);
}

void	executer(t_shell *shell, char **argv)
{

	if (!buildins(shell, argv))
		return ;
	else
	{
		shell->pid = fork();
		if (shell->pid == 0)
		{
			execve("/bin/ls", argv, shell->env);
			ft_free_str_arr(argv);
			exit(EXIT_SUCCESS);
		}
		else
			wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	init_shell(&shell, envp);
	while (!ft_strnstr(shell.input, "exit", 5))
	{
		free(shell.input);
		shell.input = get_input(&shell);
		if (shell.input[0] == '\0')
			continue ;
		else
			executer(&shell, ft_split(shell.input, ' '));
	}
	free(shell.input);
	return (EXIT_SUCCESS);
}
