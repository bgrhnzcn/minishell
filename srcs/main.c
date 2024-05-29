/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/29 22:21:46 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(t_shell *shell)
{
	t_string	prompt;
	char	*cwd;

	cwd = NULL;
	prompt = ft_string_new("minishell@");
	cwd = get_env(shell->env, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		ft_string_cat(&prompt, cwd);
		ft_string_cat(&prompt, " > ");
		free(cwd);
	}
	else
	{
		ft_string_cat(&prompt, cwd + 4);
		ft_string_cat(&prompt, "> ");
	}
	return (prompt);
}

void	init_shell(t_shell *shell, char **envp)
{
	init_env(&shell->env, envp, ENV_LIMIT);
	shell->input = malloc(0);
}

char	*get_input(t_shell *shell)
{
	t_string	input;
	t_string	prompt;

	prompt = create_prompt(shell);
	input = readline(prompt);
	ft_string_free(prompt);
	return (input);
}

int	buildins(t_shell *shell, char **argv)
{
	if (ft_strnstr(argv[0], "env", 4))
		env(shell->env);
	else if (ft_strnstr(argv[0], "pwd", 4))
		pwd(shell->env);
	else if (ft_strnstr(argv[0], "cd", 3))
		cd(&shell->env, argv[1]);
	else if (ft_strnstr(argv[0], "export", 7))
		export(&shell->env, "Deneme", "999999999999999999999");
	else if (ft_strnstr(argv[0], "unset", 6))
		unset(&shell->env, "Deneme");
	else
		return (1);
	return (0);
}

void	executer(t_shell *shell, char **argv)
{
	char	**paths;

	if (argv[0])
	paths = get_env(shell->env, "PATH");
	if (paths == NULL)
	if (!buildins(shell, argv))
		return ;
	else
	{

		shell->pid = fork();
		if (shell->pid == 0)
		{
			execve(, argv, shell->env);
			exit(EXIT_SUCCESS);
		}
		else
			wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	if (argc != 1)
		return (EXIT_FAILURE);
	init_shell(&shell, envp);
	while (!ft_strnstr(shell.input, "exit", 5))
	{
		free(shell.input);
		shell.input = get_input(&shell);
		executer(&shell, ft_split(shell.input, ' '));
	}
	free(shell.input);
	return (EXIT_SUCCESS);
}
