/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:44:58 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/05 14:59:50 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	single_command(t_shell *shell, t_cmd *cmd)
{
	int		status;

	if (!buildins(shell, cmd))
		return (status = 0, EXIT_SUCCESS);
	shell->pid = fork();
	if (shell->pid == 0)
	{
		if (!apply_redirs(cmd))
			executer(shell, cmd->argv);
		free_cmd(cmd);
		exit(127);
	}
	free_cmd(cmd);
	waitpid(shell->pid, &status, 0);
	return (EXIT_SUCCESS);
}

int	buildins(t_shell *shell, t_cmd *cmd)
{
	save_std_io(shell);
	if (ft_strequ(cmd->argv[0], "exit") && !apply_redirs(cmd))
		mini_exit(shell, EXIT_SUCCESS);
	if (ft_strequ(cmd->argv[0], "env") && !apply_redirs(cmd))
		mini_env(shell->env);
	else if (ft_strequ(cmd->argv[0], "pwd") && !apply_redirs(cmd))
		mini_pwd(shell->env);
	else if (ft_strequ(cmd->argv[0], "cd") && !apply_redirs(cmd))
		mini_cd(shell->env, cmd->argv[1]);
	else if (ft_strequ(cmd->argv[0], "export") && !apply_redirs(cmd))
		mini_export(shell, cmd->argv);
	else if (ft_strequ(cmd->argv[0], "unset") && !apply_redirs(cmd))
		mini_unset(shell, cmd->argv);
	else if (ft_strequ(cmd->argv[0], "echo") && !apply_redirs(cmd))
		mini_echo(cmd->argv);
	else
		return (restore_std_io(shell), EXIT_FAILURE);
	return (restore_std_io(shell), EXIT_SUCCESS);
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

char	**split_path(t_shell *shell)
{
	char	**paths;
	char	*cmd;

	cmd = get_env(shell->env, "PATH");
	if (cmd == NULL)
		return (NULL);
	paths = ft_split(cmd, ':');
	if (paths == NULL)
		return (free(cmd), NULL);
	free(cmd);
	return (paths);
}

void	executer(t_shell *shell, char **argv)
{
	char	**paths;
	char	*cmd;
	int		path_index;

	paths = split_path(shell);
	path_index = 0;
	while (paths[path_index] != NULL)
	{
		cmd = search_in_path(paths[path_index++], argv[0]);
		if (cmd != NULL)
			break ;
	}
	ft_free_str_arr(paths);
	if (execve(cmd, argv, shell->env))
		perror("minishell");
	free(cmd);
	ft_free_str_arr(argv);
	exit(127);
}
