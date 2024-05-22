/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/23 01:12:08 by bgrhnzcn         ###   ########.fr       */
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
	ft_strlcat(prompt, "@archlinux ", 300);
	ft_strlcat(prompt, cwd, 300);
	ft_strlcat(prompt, "]$ ", 300);
	return (prompt);
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
	int	i;

	i = 0;
	while (ft_strncmp(env[i], var, ft_strlen(var)))
		i++;
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
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
	i = 0;
	while (ft_strncmp((*env)[i], var, ft_strlen(var)))
		i++;
	free((*env)[i]);
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
	envi = ft_vector_new(sizeof(t_string));
	envi = init_env(envp);
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
			cd(&envi, "/bin");
	}
	free(input);
	return (0);
}
