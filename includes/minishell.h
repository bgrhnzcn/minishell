/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:19:50 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/14 13:50:07 by bgrhnzcn         ###   ########.fr       */
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

# define UNIMPLEMENTED(str) printf(str)

static const char	g_whitespaces[7] = " \t\n\r\v\f";
static const char	g_token_type_str[13][20] = {"HEAD", "PIPE", "OUTPUT", "INPUT", "APPEND",
	"WORD", "HEREDOC", "QUOTE", "DOUBLE_QUOTE", "DOLLAR", "WHITESPACE", "COMMAND", "TAIL"};

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
	DOLLAR,
	WHITESPACE,
	COMMAND,
	TAIL
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*text;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	char		**env;
	char		*input;
	char		**argv;
	t_token		token_list;
	pid_t		pid;
}	t_shell;

//---------------------------- Tokenizer ---------------------------------

t_token	*new_token(t_token_type type, char *text);
void	print_token(t_token *token);
void	print_tokens(t_token *token_list);
void	clear_tokens(t_token *token_list);
void	destroy_token(t_token *token);
t_bool	add_token_last(t_token *tokens, t_token *token);
t_bool	add_token_after(t_token *before, t_token *new);
t_token	*remove_token(t_token *tokens, t_token *token);
t_token	*remove_sublist(t_token *list_start, t_token *list_end);



//------------------------------ Parser ----------------------------------

t_token	*parse_input(t_token *token_list, char *input);
void 	check_quotes(t_token *token_list);
t_bool	check_syntax(t_token *token_list, char **env);
void	perform_expansion(t_token *token_list, char **env);
void	join_cont_words(t_token *token_list);
void	remove_whitespaces(t_token *token_list);
char	**create_argv(t_token *token_list);
t_bool	pipe_check(t_token *token_list);

//---------------------------- Commands ---------------------------------

int	get_command_count(t_token *token_list);
t_bool	create_commands(t_token **commands, int command_count, t_token *token_list);

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
