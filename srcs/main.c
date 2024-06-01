/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/01 21:02:06 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*cwd;

	cwd = NULL;
	prompt = ft_calloc(200, sizeof(char));
	ft_strlcat(prompt, "minishell@", 200);
	cwd = get_env(shell->env, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		ft_strlcat(prompt, ft_strrchr(cwd, '/'), 200);
		ft_strlcat(prompt, " > ", 200);
		free(cwd);
	}
	else
	{
		ft_strlcat(prompt, ft_strrchr(cwd, '/'), 200);
		ft_strlcat(prompt, "> ", 200);
	}
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
	if (ft_strequ(argv[0], "exit"))
		mini_exit(shell, EXIT_SUCCESS);
	if (ft_strequ(argv[0], "env"))
		mini_env(shell->env);
	else if (ft_strequ(argv[0], "pwd"))
		mini_pwd(shell->env);
	else if (ft_strequ(argv[0], "cd"))
		mini_cd(shell->env, argv[1]);
	else if (ft_strequ(argv[0], "export"))
		mini_export(shell, argv);
	else if (ft_strequ(argv[0], "unset"))
		mini_unset(shell, argv[1]);
	else
		return (1);
	return (0);
}

void	executer(t_shell *shell, char **argv)
{
	//char	**paths;
	char	*test;

	if (!buildins(shell, argv))
		return ;
	else
	{
		//paths = ft_split(get_env(shell->env, "PATH"), ':');
		test = ft_calloc(300, sizeof (char));
		ft_strlcat(test, "/usr/bin/", 300);
		ft_strlcat(test, argv[0], 300);
		shell->pid = fork();
		if (shell->pid == 0)
		{
			if (execve(test, argv, shell->env))
				printf("%s:%s\n", test, strerror(errno));
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
	while (true)
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
