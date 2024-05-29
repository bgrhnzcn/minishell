/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:30 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/30 00:23:03 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_index(t_str_vec env, t_string var)
{
	size_t	i;

	i = 0;
	while (i < ft_vector_len(&env) - 1)
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env(t_str_vec env, char *var)
{
	int	i;

	i = find_env_index(env, var);
	if (i == -1)
		return (NULL);
	return (env[i]);
}

//void	set_env(t_str_vec *env, char *var, char *value)
//{
//	char	*var_title;
//	char	*temp;
//	int		i;
//
//	temp = get_env(*env, var);
//	if (temp == NULL)
//	{
//		var_title = ft_string_new(var);
//		ft_string_cat(&var_title, "=");
//		ft_string_cat(&var_title, value);
//		ft_vector_insert(env, &var_title, ft_vector_len(env) - 1);
//		return ;
//	}
//	i = find_env_index(*env, var);
//	if (i == -1)
//		return ;
//	ft_vector_remove(env, &temp, i);
//	ft_string_free(temp);
//	var_title = ft_string_new(var);
//	ft_string_cat(&var_title, "=");
//	ft_string_cat(&var_title, value);
//	ft_vector_insert(env, &var_title, i);
//}
/*important environments:
PWD, 
*/
//t_str_vec	init_env(char **envp)
//{
//	t_str_vec	env;
//	t_string	temp;
//
//	env = ft_vector_new(sizeof(t_string));
//	while (*envp != NULL)
//	{
//		temp = ft_string_new(*envp);
//		ft_vector_append(&env, &temp);
//		envp++;
//	}
//	ft_vector_append(&env, &(char **){NULL});
//	return env;
//}

int	set_env(t_env_map envs, char *var)
{
	size_t	index;

	index = (envs.hash(var, ft_strlen(var)) % envs.buffer_size);
	if (envs.buffer[index].is_free == true)
		envs.buffer[index] = (t_env)
			{.is_free = false, .var = var, .next = NULL};
	else if (ft_strnstr(envs.buffer[index].var, var,))

}

void	init_env(t_env_map *envs, char **envp)
{
	char		*var;

	envs->buffer_size = ENV_LIMIT - 1;
	envs->hash = ft_hash;
	envs->buffer = ft_calloc(ENV_LIMIT, sizeof (t_env));
	if (envs->buffer == NULL)
		return (NULL);
	envs->buffer[envs->buffer_size] = (t_env)
		{.is_free = false, .var = NULL, .next = NULL};
	while (*envp)
	{
		set_env(*envs, ft_substr(*envp, 0, ft_strlen(*envp)));
		envp++;
	}
}

void	mini_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
