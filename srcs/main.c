/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/24 18:48:06 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(t_str_vec env)
{
	char	*prompt;
	char	*cwd;

	cwd = NULL;
	prompt = ft_calloc(300, sizeof(char));
	cwd = get_env(env, "PWD");
	ft_strlcat(prompt, "minishell - ", 300);
	ft_strlcat(prompt, cwd, 300);
	return (prompt);
}

char	*get_input(t_str_vec env)
{
	t_string	input;
	t_string	prompt;

	prompt = create_prompt(env);
	input = readline(prompt);
	free(prompt);
	return (input);
}

t_str_vec	init_env(char **envp)
{
	t_str_vec	env;
	t_string	temp;

	env = ft_vector_new(sizeof(t_string));
	while (*envp != NULL)
	{
		temp = ft_string_new(*envp);
		ft_vector_append(&env, &temp);
		envp++;
	}
	ft_vector_append(&env, &(char **){NULL});
	return env;
}

char	*get_env(t_str_vec env, char *var)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_len(&env) - 1)
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	set_env(t_str_vec *env, char *var, char *value)
{
	char	*var_title;
	char	*temp;
	int		i;

	temp = get_env(*env, var);
	if (temp == NULL)
	{
		var_title = ft_string_new(var);
		ft_string_cat(&var_title, "=");
		ft_string_cat(&var_title, value);
		ft_vector_append(env, &var_title);
		return ;
	}
	
	ft_vector_remove(env, &temp, i);
	ft_string_free(temp);
	var_title = ft_string_new(var);
	ft_string_cat(&var_title, "=");
	ft_string_cat(&var_title, value);
	ft_vector_insert(env, &var_title, i);
}

int	main(int argc, char **argv, char **envp)
{
	t_str_vec	envi;
	char		*input;
	pid_t		pid;

	(void)argc;
	envi = init_env(envp);
	input = malloc(0);
	while (!ft_strnstr(input, "exit", 5))
	{
		free(input);
		input = get_input(envi);
		if (ft_strnstr(input, "clear", 6))
		{
			pid = fork();
			if (pid == 0)
			{
				execve("/bin/clear", argv, envi);
				exit(EXIT_SUCCESS);
			}
			else
				wait(NULL);
		}
		if (ft_strnstr(input, "env", 4))
		{
			pid = fork();
			if (pid == 0)
				env(envi);
			else
				wait(NULL);
		}
		if (ft_strnstr(input, "pwd", 4))
		{
			pid = fork();
			if (pid == 0)
				pwd(envi);
			else
				wait(NULL);
		}
		if (ft_strnstr(input, "cd", 3))
			cd(&envi, NULL);
	}
	free(input);
	return (0);
}
