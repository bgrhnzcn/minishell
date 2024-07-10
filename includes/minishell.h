/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:19:50 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/10 17:18:08 by buozcan          ###   ########.fr       */
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

static const char	g_whitespaces[6] = " \t\n\r\v\f";

typedef enum e_token_type
{
	HEAD,
	PIPE,
	OUTPUT,
	INPUT,
	APPEND,
	WORD,
	HEREDOC,
	QUOTE,
	DOUBLE_QUOTE,
	DOLLAR
}	t_token_type;

typedef	struct s_token
{
	t_token_type	type;
	int				index;
	char			*text;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	char		**env;
	char		*input;
	t_token		token_list;
	pid_t		pid;
}	t_shell;

//---------------------------- Tokenizer ---------------------------------

t_token	*new_token(t_token_type type, int index, char *text);
t_bool	add_token_last(t_token *tokens, t_token *token);
void	print_tokens(t_token *token_list);
void	clear_tokens(t_token *token_list);
void 	check_quotes(t_token *token_list,char **env);

//------------------------------ Parser ----------------------------------

t_token	*parse_input(t_token *token_list, char *input);

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
