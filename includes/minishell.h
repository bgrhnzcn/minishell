/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:19:50 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/25 23:15:44 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include "sys/wait.h"
# include "sys/types.h"
# include "libft.h"

# define ENV_LIMIT			1000
# define ANSI_COLOR_BLUE	"\e[0;94m"
# define ANSI_COLOR_RESET	"\x1b[0m"
# define ANSI_COLOR_GREEN	"\e[1;92m"

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
	int			saved_stdin;
	int			saved_stdout;
	int			fdin;
	int			fdout;
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

t_bool	parse_input(t_token *token_list, char *input);
t_bool	check_quotes(t_token *token_list);
t_bool	check_syntax(t_token *token_list, char **env);
void	perform_expansion(t_token *token_list, char **env);
void	join_cont_words(t_token *token_list);
void	remove_whitespaces(t_token *token_list);
char	**create_argv(t_token *token_list);
t_bool	pipe_check(t_shell *shell, t_token *token_list);

//------------------------- I/O Opeartions ------------------------------

void	apply_redirs(t_shell *shell, t_token *command);

//---------------------------- Commands ---------------------------------

int		get_command_count(t_token *token_list);
t_token	**create_commands(int command_count, t_token *token_list);

//---------------------------- Executer ---------------------------------

int		buildins(t_shell *shell, char **argv);
void	executer(t_shell *shell, char **argv);

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
