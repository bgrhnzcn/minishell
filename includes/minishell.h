/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:45:16 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/24 14:50:19 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file minishell.h
 * @brief Header file for the minishell program.
 *
 * This file contains the declarations of various functions and data structures
 * used in the minishell program. It includes the necessary header files and
 * defines constants and macros used throughout the program.
 */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "sys/types.h"
# include "sys/wait.h"
# include <sys/ioctl.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>

/**
 * @def ENV_LIMIT
 * The maximum number of environment variables allowed.
 */
# define ENV_LIMIT			1000
# define MAIN_P				0
# define CHILD_P			1
# define HEREDOC_P			2
# define AFTER_IN_P			3

/**
 * @def ANSI_COLOR_BLUE
 * ANSI escape code for blue color.
 */
# define ANSI_COLOR_BLUE		"\e[0;94m"

/**
 * @def ANSI_COLOR_RED
 * ANSI escape code for red color.
 */
# define ANSI_COLOR_RED		"\e[0;91m"

/**
 * @def ANSI_COLOR_GREEN
 * ANSI escape code for green color.
 */
# define ANSI_COLOR_GREEN	"\e[1;92m"

/**
 * @def ANSI_COLOR_RESET
 * ANSI escape code to reset color.
 */
# define ANSI_COLOR_RESET	"\x1b[0m"

extern int	g_global_exit;

/**
 * @var g_whitespaces
 * Array of characters representing different types of whitespaces.
 */
static const char	g_whitespaces[7] = " \t\n\r\v\f";

/**
 * @var g_token_type_str
 * Array of strings representing different token types.
 */
static const char	g_token_type_str[14][20] = {
	"HEAD",			"PIPE",		"OUTPUT",	"INPUT",		"APPEND",
	"WORD",			"HEREDOC",	"QUOTE",	"DOUBLE_QUOTE",	"DOLLAR",
	"QUOTED_DOLLAR", "WHITESPACE",	"COMMAND",	"TAIL"};

/**
 * @enum t_token_type
 * Enumeration of different token types.
 */
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

/**
 * @struct t_token
 * Structure representing a token.
 */
typedef struct s_token
{
	char			*text;	/**< The text of the token. */
	struct s_token	*next;	/**< Pointer to the next token. */
	struct s_token	*prev;	/**< Pointer to the previous token. */
	t_token_type	type;	/**< The type of the token. */
}	t_token;

/**
 * @struct t_cmd
 * Structure representing a command.
 */
typedef struct s_cmd
{
	t_token	*redir_list;		/**< List of redirection tokens. */
	char	**argv;				/**< Array of arguments for the command. */
	int		fdin;				/**< File descriptor for input redirection. */
	int		fdout;				/**< File descriptor for output redirection. */
	int		heredoc_pipe[2];	/**< Pipe for heredoc redirection. */
	t_bool	fd_fail;			/**< Flag indicating if file descriptor failure. */
}	t_cmd;

/**
 * @struct t_shell
 * Structure representing the minishell.
 */
typedef struct s_shell
{
	t_token	token_list;		/**< The list of tokens. */
	char	**env;			/**< Array of environment variables. */
	char	*input;			/**< The input string. */
	pid_t	pid;			/**< Process ID of the shell. */
	int		saved_stdin;	/**< Saved standard input file descriptor. */
	int		saved_stdout;	/**< Saved standard output file descriptor. */
	int		*pipes;			/**< Array of pipe file descriptors. */
	int		status;			/**< Status of the last command. */
	t_bool	is_heredoc_open;
}	t_shell;

//---------------------------- Tokenizer ---------------------------------

/**
 * @brief Creates a new token.
 *
 * @param type The type of the token.
 * @param text The text of the token.
 * @return A pointer to the newly created token.
 */
t_token	*new_token(t_token_type type, char *text);

/**
 * @brief Prints the details of a token.
 *
 * @param token The token to be printed.
 */
void	print_token(t_token *token);

/**
 * @brief Prints the details of all tokens in a token list.
 *
 * @param token_list The token list to be printed.
 */
void	print_tokens(t_token *token_list);

/**
 * @brief Clears all tokens in a token list.
 *
 * @param token_list The token list to be cleared.
 */
void	clear_tokens(t_token *token_list);

/**
 * @brief Destroys a token.
 *
 * @param token The token to be destroyed.
 */
void	destroy_token(t_token *token);

/**
 * @brief Adds a token to the end of a token list.
 *
 * @param tokens The token list.
 * @param token The token to be added.
 * @return True if the token was added successfully, false otherwise.
 */
t_bool	add_token_last(t_token *tokens, t_token *token);

/**
 * @brief Adds a token after a given token in a token list.
 *
 * @param before The token after which the new token should be added.
 * @param new The new token to be added.
 * @return True if the token was added successfully, false otherwise.
 */
t_bool	add_token_after(t_token *before, t_token *new);

/**
 * @brief Removes a token from a token list.
 *
 * @param tokens The token list.
 * @param token The token to be removed.
 * @return The token that was removed.
 */
t_token	*remove_token(t_token *tokens, t_token *token);

/**
 * @brief Removes a sublist of tokens from a token list.
 *
 * @param list_start The start of the sublist.
 * @param list_end The end of the sublist.
 * @return The start of the remaining token list.
 */
t_token	*remove_sublist(t_token *list_start, t_token *list_end);

//------------------------------ Parser ----------------------------------

/**
 * @brief Parses the input string and creates a token list.
 *
 * @param token_list The token list to be created.
 * @param input The input string.
 * @return True if the input was parsed successfully, false otherwise.
 */
t_bool	parse_input(t_token *token_list, char *input);

/**
 * @brief Checks if the quotes in the token list are balanced.
 *
 * @param token_list The token list.
 * @return True if the quotes are balanced, false otherwise.
 */
t_bool	check_quotes(t_token *token_list);

/**
 * @brief Checks the syntax of the token list.
 *
 * @param token_list The token list.
 * @param env The array of environment variables.
 * @return True if the syntax is correct, false otherwise.
 */
t_bool	check_syntax(t_token *token_list, char **env);

/**
 * @brief Merges consecutive redirection tokens into a single token.
 *
 * @param token_list The token list.
 */
void	merge_redirs(t_token *token_list);

/**
 * @brief Performs variable expansion in the token list.
 *
 * @param token_list The token list.
 * @param env The array of environment variables.
 */
void	perform_expansion(t_token *token_list, char **env);

/**
 * @brief Joins consecutive word tokens into a single token.
 *
 * @param token_list The token list.
 */
void	join_cont_words(t_token *token_list);

/**
 * @brief Removes all whitespace tokens from the token list.
 *
 * @param token_list The token list.
 */
void	remove_whitespaces(t_token *token_list);

/**
 * @brief Creates an array of arguments from the token list.
 *
 * @param token_list The token list.
 * @return The array of arguments.
 */
char	**create_argv(t_token *token_list);

/**
 * @brief Checks if a pipe is present in the token list.
 *
 * @param shell The minishell structure.
 * @param token_list The token list.
 * @return True if a pipe is present, false otherwise.
 */
t_bool	pipe_check(t_shell *shell, t_token *token_list);

//------------------------- I/O Operations ------------------------------

/**
 * @brief Gets the heredoc input for a command.
 *
 * @param cmd The command structure.
 */
int	get_heredoc(t_cmd *cmd);

/**
 * @brief Gets the input/output redirections for a command.
 *
 * @param cmd The command structure.
 * @param command The token representing the command.
 * @return True if the redirections were obtained successfully, false otherwise.
 */
t_bool	get_redirs(t_cmd *cmd);

/**
 * @brief Applies the input/output redirections for a command.
 *
 * @param cmd The command structure.
 * @return True if the redirections were applied successfully, false otherwise.
 */
t_bool	apply_redirs(t_cmd *cmd);

/**
 * @brief Saves the standard input/output file descriptors.
 *
 * @param shell The minishell structure.
 */
void	save_std_io(t_shell *shell);

/**
 * @brief Restores the standard input/output file descriptors.
 *
 * @param shell The minishell structure.
 */
void	restore_std_io(t_shell *shell);

/**
 * @brief Waits for all child processes to terminate.
 * 
 * This function waits for all child processes to terminate before returning.
 * It ensures that the parent process does not exit before all child processes
 * have completed their execution.
 */
void	signal_cont(int status);

/**
 * @brief Prints an error message to the console.
 *
 * @param cmd The command that caused the error.
 * @param err The error code.
 */
void	print_error(char *cmd, int err);

/**
 * @brief Creates pipes for inter-process communication.
 *
 * @param p The pointer to the array of pipe file descriptors.
 * @param command_count The number of commands that require pipes.
 */
void	create_pipes(int **p, int command_count);

/**
 * @brief Clears the allocated memory for pipes.
 *
 * @param pipes The array of pipe file descriptors.
 * @param command_count The number of commands that require pipes.
 */
void	clear_pipes(int *pipes, int command_count);

/**
 * @brief Closes the specified pipes, leaving one pipe open.
 *
 * @param pipes The array of pipe file descriptors.
 * @param command_count The number of commands that require pipes.
 * @param not_close The index of the pipe that should not be closed.
 */
void	close_pipes(int *pipes, int command_count, int not_close);

//---------------------------- Commands ---------------------------------

///**
// * @brief Prints the commands in the token list.
// *
// * @param commands The array of commands.
// * @param command_count The number of commands.
// */
//void	print_commands(t_cmd *commands, int command_count);
//
///**
// * @brief Prints a single command.
// *
// * @param command The command structure.
// * @param i The index of the command.
// */
//void	print_command(t_cmd *command, int i);

/**
 * @brief Gets the number of commands in the token list.
 *
 * @param token_list The token list.
 * @return The number of commands.
 */
int		get_command_count(t_token *token_list);

/**
 * @brief Creates an array of commands from the token list.
 *
 * @param command_count The number of commands.
 * @param token_list The token list.
 * @return The array of commands.
 */
t_cmd	*create_commands(int command_count, t_token *token_list);

/**
 * @brief Frees the memory allocated for a command structure.
 *
 * @param cmd The command structure.
 */
void	free_cmd(t_cmd *cmd);

/**
 * @brief Frees the memory allocated for an array of command structures.
 *
 * @param commands The array of commands.
 * @param command_count The number of commands.
 */
void	free_cmds(t_cmd *commands, int command_count);

//---------------------------- Executer ---------------------------------

/**
 * @brief Splits the PATH environment variable into an array of paths.
 *
 * @param shell The minishell structure.
 * @return The array of paths.
 */
char	**split_path(t_shell *shell);

/**
 * Executes the built-in commands in the minishell.
 *
 * This function is responsible for executing
 * the built-in commands in the minishell.
 * It takes a pointer to the `t_shell` struct and
 * a pointer to the `t_cmd` struct as parameters.
 *
 * @param shell A pointer to the `t_shell` struct representing the minishell.
 * @param cmd A pointer to the `t_cmd` struct
 * representing the command to be executed.
 * @return An integer representing the status of the execution.
 */
int		buildins(t_shell *shell, t_cmd *cmd);

/**
 * @brief Executes a single command in the minishell.
 *
 * This function is responsible for executing a single command in the minishell.
 * It takes a pointer to the shell structure and a pointer to the command
 * structure as parameters.
 *
 * @param shell A pointer to the shell structure.
 * @param cmd A pointer to the command structure.
 * @return The boolean result indicating the success or
 * failure of the command execution.
 */
t_bool	single_command(t_shell *shell, t_cmd *cmd);

/**
 * @brief Executes the built-in commands or external programs.
 *
 * @param shell The minishell structure.
 * @param argv The array of command-line arguments.
 */
void	executer(t_shell *shell, char **argv);

/**
 * @brief Waits for all child processes to terminate.
 *
 * This function waits for all child processes to terminate before returning.
 * It ensures that the parent process does not exit before all child processes
 * have completed their execution.
 */
void	wait_all_childs(void);

/**
 * @brief Gets the value of an environment variable.
 *
 * @param env The array of environment variables.
 * @param var The name of the variable.
 * @return The value of the variable, or NULL if not found.
 */
char	*get_env(char **env, char *var);

/**
 * @brief Sets the value of an environment variable.
 *
 * @param env The array of environment variables.
 * @param var The name of the variable.
 * @param value The value to be set.
 */
void	set_env(char **env, char *var, char *value);

/**
 * @brief Finds the index of an environment variable.
 *
 * @param env The array of environment variables.
 * @param var The name of the variable.
 * @return The index of the variable, or -1 if not found.
 */
int		find_env_index(char **env, char *var);

/**
 * @brief Initializes the environment variables.
 *
 * @param shell The minishell structure.
 * @param envp The array of environment variables.
 * @return The number of environment variables.
 */
int		init_env(t_shell *shell, char **envp);

/**
 * @brief Prints the environment variables.
 *
 * @param env The array of environment variables.
 */
void	mini_env(char **env);

/**
 * @brief Prints the current working directory.
 *
 * @param env The array of environment variables.
 */
void	mini_pwd(char **env);

/**
 * @brief Changes the current working directory.
 *
 * @param env The array of environment variables.
 * @param path The path to the directory.
 */
void	mini_cd(char **env, char *path);

/**
 * @brief Prints the arguments to the console.
 *
 * @param av The array of arguments.
 */
void	mini_echo(char **av);

/**
 * @brief Adds or modifies an environment variable.
 *
 * @param shell The minishell structure.
 * @param argv The array of arguments.
 */
void	mini_export(t_shell *shell, char **argv);

/**
 * @brief Removes an environment variable.
 *
 * @param shell The minishell structure.
 * @param argv The array of arguments.
 */
void	mini_unset(t_shell *shell, char **argv);
char	**create_env_variable(t_shell *shell, const char *arg, int *found);
void 	remove_env(t_shell *shell, const char *arg);
int		count_env_variables(char **env);
size_t	counter_argv(char *str);
char	**envs(int size);

/**
 * @brief Exits the minishell program.
 *
 * @param shell The minishell structure.
 * @param status The exit status.
 */
void	mini_exit(t_shell *shell, t_cmd *cmd);

//--------------------export_utils----------------//
int	check_env(t_shell *shell, const char *identifier, const char *arg);
int	add_new_env(t_shell *shell, const char *arg);
int	valid_identifier(const char *str);

#endif
