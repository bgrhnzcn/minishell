/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:19:50 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/06/01 17:22:02 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include "sys/wait.h"
# include "sys/types.h"
# include "libft.h"

# define ENV_LIMIT 1000

typedef struct s_shell
{
	char		**env;
	char		*input;
	pid_t		pid;
}	t_shell;

char	*get_env(char ** env, char *var);
void	set_env(char **env, char *var, char *value);
int		find_env_index(char **env, char *var);
int		init_env(t_shell *shell, char **envp);
void	debug_str(t_string str);
void	debug_env(t_str_vec env);

void	mini_env(char ** env);
void	mini_pwd(char ** env);
void	mini_cd(char ** env, char *path);
void	mini_export(t_shell *shell, char **argv);
void	mini_unset(t_shell *shell, char *var);
void	mini_exit(t_shell *shell, int status);

#endif
