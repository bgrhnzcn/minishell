/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:44:58 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/28 16:14:06 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	single_command(t_shell *shell, t_cmd *cmd)
{
	int	status;

	g_global_exit = 0;
	if (get_redirs(cmd))
		return (EXIT_FAILURE);
	if (g_global_exit == 130)
		return (EXIT_FAILURE);
	if (cmd != NULL && !buildins(shell, cmd))
		return (EXIT_SUCCESS);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal_cont(CHILD_P);
		if (cmd != NULL)
		{
			if (cmd->argv[0] != NULL && !apply_redirs(cmd))
				executer(shell, cmd->argv);
			free_cmd(cmd);
		}
		exit(g_global_exit);
	}
	waitpid(cmd->pid, &status, 0);
	process_exit_code(status);
	return (EXIT_SUCCESS);
}

static char	*search_in_path(const char *path, const char *command)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*cmd;
	int				cmd_size;

	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	cmd_size = ft_strlen(path) + ft_strlen(command) + 2;
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (ft_strequ(command, dirent->d_name))
		{
			cmd = ft_calloc(cmd_size, sizeof (char));
			if (cmd == NULL)
				break ;
			ft_strlcat(cmd, path, cmd_size);
			ft_strlcat(cmd, "/", cmd_size);
			return (ft_strlcat(cmd, command, cmd_size), closedir(dir), cmd);
		}
		dirent = readdir(dir);
	}
	return (closedir(dir), NULL);
}

static void	execute_relative(t_shell *shell, char **argv)
{
	int		err;
	char	*pwd;
	char	*cmd;
	char	*temp;

	if (ft_strchr(argv[0], '/') == argv[0])
		pwd = ft_strdup("");
	else
		pwd = get_env(shell->env, "PWD");
	temp = ft_strjoin(pwd + 4, "/");
	free(pwd);
	cmd = ft_strjoin(temp, argv[0]);
	free(temp);
	if (execve(cmd, argv, shell->env))
	{
		err = errno;
		print_error(argv[0], err);
		if (err == ENOENT)
			g_global_exit = 127;
		else if (err == EACCES)
			g_global_exit = 126;
	}
	free(cmd);
}

static void	execute_path(t_shell *shell, char **argv)
{
	char	**paths;
	char	*cmd;
	int		path_index;

	path_index = 0;
	paths = split_path(shell);
	while (paths != NULL && paths[path_index] != NULL)
	{
		cmd = search_in_path(paths[path_index++], argv[0]);
		if (cmd != NULL)
			break ;
	}
	if (paths == NULL)
		cmd = ft_strdup(argv[0]);
	ft_free_str_arr(paths);
	if (execve(cmd, argv, shell->env))
	{
		ft_putstr_fd("Command \'", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd("\' not found.\n", STDERR_FILENO);
		g_global_exit = 127;
	}
	free(cmd);
}

void	executer(t_shell *shell, char **argv)
{
	if (ft_strchr(argv[0], '/') != NULL)
		execute_relative(shell, argv);
	else
		execute_path(shell, argv);
}
