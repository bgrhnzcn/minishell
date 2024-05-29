/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:19:50 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/29 23:07:27 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include "sys/wait.h"
# include "sys/types.h"
# include "libft.h"

# define ENV_LIMIT 500

typedef struct s_env
{
	char			*var;
	t_bool			is_free;
	struct s_env	next;
}	t_env;

typedef struct s_env_map
{
	//Main buffer to store data.
	t_env	*buffer;
	//Buffer size as sizeof(char *).
	size_t	buffer_size;
	//Function for hashing. We store in here for consistency.
	size_t	(*hash)(void *, size_t);
}	t_env_map;

typedef struct s_shell
{
	t_env_map	env;
	t_string	input;
	pid_t		pid;
}	t_shell;

char	*get_env(t_env_map env, char *var);
int		set_env(t_env_map env, char *var, char *value);
int		find_env_index(t_str_vec env, t_string var);
void	init_env(t_env_map *envs, char **envp, size_t env_limit);
void	debug_str(t_string str);
void	debug_env(t_str_vec env);

void	mini_env(t_env_map env);
void	mini_pwd(t_env_map env);
void	mini_cd(t_env_map env, char *path);
void	mini_export(t_env_map env, char *var, char *value);
void	mini_unset(t_env_map env, t_string var);

#endif
