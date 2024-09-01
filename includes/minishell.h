/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:45:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/01 18:52:09 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------ Includes -----------------------------------//

# include "libft.h"
# include "sys/types.h"
# include "sys/wait.h"
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>

//------------------------------- Defines ------------------------------------//

# define ENV_LIMIT			1000
# define MAIN_P				0
# define CHILD_P			1
# define HEREDOC_P			2
# define AFTER_IN_P			3
# define ANSI_COLOR_BLUE	"\e[0;94m"
# define ANSI_COLOR_RED		"\e[0;91m"
# define ANSI_COLOR_GREEN	"\e[1;92m"
# define ANSI_COLOR_RESET	"\x1b[0m"

//------------------------------- Globals -----------------------------------//

extern int			g_global_exit;

static const char	g_whitespaces[7] = " \t\n\r\v\f";

//------------------------------- Typedefs ----------------------------------//

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
	QUOTED_DOLLAR,
	WHITESPACE,
	COMMAND,
	TAIL
}	t_token_type;

typedef struct s_token
{
	char			*text;
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	type;
}	t_token;

typedef struct s_cmd
{
	pid_t	pid;
	t_token	*redir_list;
	char	**argv;
	int		fdin;
	int		fdout;
	int		heredoc_pipe[2];
	t_bool	fd_fail;
}	t_cmd;

typedef struct s_shell
{
	t_token	token_list;
	char	**env;
	char	*input;
	int		saved_stdin;
	int		saved_stdout;
	int		*pipes;
	int		status;
	t_bool	is_heredoc_open;
	int		j;
}	t_shell;

//------------------------------- Main --------------------------------------//

char	*create_prompt(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
char	*get_input(t_shell *shell);
t_bool	parse(t_shell *shell);

//---------------------------- Tokenizer ------------------------------------//

t_token	*new_token(t_token_type type, char *text);
void	clear_tokens(t_token *token_list);
void	destroy_token(t_token *token);
t_bool	add_token_last(t_token *tokens, t_token *token);
t_bool	add_token_after(t_token *before, t_token *new);
t_token	*remove_token(t_token *tokens, t_token *token);
t_token	*remove_sublist(t_token *list_start, t_token *list_end);

//------------------------------ Parser -------------------------------------//

t_bool	parse_input(t_token *token_list, char *input);
t_bool	check_quotes(t_token *token_list);
t_bool	check_syntax(t_token *token_list, char **env);
void	merge_redirs(t_token *token_list);
void	split_dollar(char *env, t_token *dollar);
void	create_joined_words(t_token *tokens);
void	perform_expansion(t_token *token_list, char **env);
void	join_cont_words(t_token *token_list);
void	remove_whitespaces(t_token *token_list);
char	**create_argv(t_token *token_list);
t_bool	pipe_check(t_shell *shell, t_token *token_list);

//------------------------- I/O Operations ----------------------------------//

int		get_heredoc(t_cmd *cmd);
t_bool	get_redirs(t_cmd *cmd);
t_bool	apply_redirs(t_cmd *cmd);
void	save_std_io(t_shell *shell);
void	restore_std_io(t_shell *shell);
void	signal_cont(int status);
int		process_exit_code(int status);
void	print_error(char *cmd, int err);
void	create_pipes(int **p, int command_count);
void	clear_pipes(int *pipes, int command_count);
void	close_pipes(int *pipes, int command_count, int not_close);

//---------------------------- Commands -------------------------------------//

int		get_command_count(t_token *token_list);
t_cmd	*create_commands(int command_count, t_token *token_list);
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmd *commands, int command_count);

//---------------------------- Executer -------------------------------------//

char	**split_path(t_shell *shell);
int		buildins(t_shell *shell, t_cmd *cmd);
t_bool	single_command(t_shell *shell, t_cmd *cmd);
void	executer(t_shell *shell, char **argv);
void	wait_all_childs(t_cmd *commands, int command_count);
int		is_dir(char *cmd, char *argv);
void	set_cmd_and_temp(t_shell *shell, char **cmd, char **temp, char **argv);

//------------------------------ Buildins -----------------------------------//

void	set_env(char **env, char *var, char *value);
int		find_env_index(char **env, char *var);
int		init_env(t_shell *shell, char **envp);
char	*get_env(char **env, char *var);
void	mini_env(char **env);
void	mini_pwd(char **env);
void	cd_print_error(char *path, int err);
void	cd_change_pwds(char **env, char *pwd);
void	ft_get_cwd(char **pwd);
void	mini_cd(char **env, t_cmd *cmd);
void	mini_echo(char **av);
void	mini_export(t_shell *shell, char **argv, int i, char *identifier);
void	mini_unset(t_shell *shell, char **argv);
void	remove_env(t_shell *shell, const char *arg);
int		count_env_variables(char **env);
size_t	counter_argv(char *str);
char	**envs(int size);
void	mini_exit(t_shell *shell, t_cmd *cmd);
int		check_env(t_shell *shell, const char *identifier, const char *arg);
int		add_new_env(t_shell *shell, const char *arg);
int		valid_identifier(const char *str);

#endif
