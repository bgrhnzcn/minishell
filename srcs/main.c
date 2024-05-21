/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/22 00:38:17 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(void)
{
	char	*prompt;
	char	*user;
	char	*cwd;

	cwd = NULL;
	prompt = ft_calloc(300, sizeof(char));
	user = getenv("USER");
	cwd = getcwd(cwd, 200);
	prompt[0] = '[';
	ft_strlcat(prompt, user, 300);
	ft_strlcat(prompt, "@", 300);
	ft_strlcat(prompt, "archlinux", 300);
	ft_strlcat(prompt, " ", 300);
	ft_strlcat(prompt, cwd, 300);
	ft_strlcat(prompt, "]$ ", 300);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	pid_t	pid;

	(void)argc;
	input = malloc(0);
	while (!ft_strnstr(input, "exit", 5))
	{
		free(input);
		input = readline(create_prompt());
		if (ft_strnstr(input, "clear", 6))
		{
			pid = fork();
			if (pid == 0)
			{
				execve("/bin/clear", argv, envp);
				exit(EXIT_SUCCESS);
			}
			else
				wait(NULL);
		}
		if (ft_strnstr(input, "env", 4))
		{
			pid = fork();
			if (pid == 0)
				env(envp);
			else
				wait(NULL);
		}
		if (ft_strnstr(input, "pwd", 4))
		{
			pid = fork();
			if (pid == 0)
				pwd();
			else
				wait(NULL);
		}
		if (ft_strnstr(input, "cd", 3))
			cd("/bin/");
	}
	free(input);
	return (0);
}
