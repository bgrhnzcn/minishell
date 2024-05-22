/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:19:50 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/23 01:09:26 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include <stdlib.h>
# include "sys/wait.h"
# include "sys/types.h"
# include "libft.h"

void	env(char **envp);
void	pwd(t_str_vec env);
char	*get_env(t_str_vec env, char *var);
void	set_env(t_str_vec *env, char *var, char *value);
void	cd(t_str_vec *env, char *path);



#endif
