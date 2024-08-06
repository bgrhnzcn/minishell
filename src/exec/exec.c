/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:44:58 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/07 00:06:29 by bgrhnzcn         ###   ########.fr       */
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
	waitpid(shell->pid, &status, 0);
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
	char	*pwd;
	char	*cmd;
	char	*temp;

	pwd = get_env(shell->env, "PWD");
	temp = ft_strjoin(pwd + 4, "/");
	free(pwd);
	cmd = ft_strjoin(temp, argv[0]);
	free(temp);
	if (execve(cmd, argv, shell->env))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	free(cmd);
}

static void	execute_path(t_shell *shell, char **argv)
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
	if (cmd != NULL && execve(cmd, argv, shell->env))
	{
		ft_putstr_fd("Command \'", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd("\' not found.\n", STDERR_FILENO);
	}
	free(cmd);
}

void	executer(t_shell *shell, char **argv)
{
	if (ft_strchr(argv[0], '/'))
		execute_relative(shell, argv);
	else
		execute_path(shell, argv);
	ft_free_str_arr(argv);
	exit(127);
}
