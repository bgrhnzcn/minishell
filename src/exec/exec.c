/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:44:58 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/21 02:42:44 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buildins(t_shell *shell, char **argv)
{
	if (ft_strequ(argv[0], "exit"))
		mini_exit(shell, EXIT_FAILURE);
	if (ft_strequ(argv[0], "env"))
		mini_env(shell->env);
	else if (ft_strequ(argv[0], "pwd"))
		mini_pwd(shell->env);
	else if (ft_strequ(argv[0], "cd"))
		mini_cd(shell->env, argv[1]);
	else if (ft_strequ(argv[0], "export"))
		mini_export(shell, argv);
	else if (ft_strequ(argv[0], "unset"))
		mini_unset(shell, argv[1]);
	else
		return (1);
	return (0);
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
			ft_strlcat(cmd, command, cmd_size);
			closedir(dir);
			return (cmd);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

void	executer(t_shell *shell, char **argv)
{
	char	**paths;
	char	*cmd;
	int		path_index;

	if (!buildins(shell, argv))
	{
		ft_free_str_arr(argv);
		return ;
	}
	else
	{
		cmd = get_env(shell->env, "PATH");
		if (cmd == NULL)
			return ;
		paths = ft_split(cmd, ':');
		free(cmd);
		path_index = 0;
		while (paths[path_index] != NULL)
		{
			cmd = search_in_path(paths[path_index++], argv[0]);
			if (cmd != NULL)
				break ;
		}
		printf("cmd: %s, argv[1]: %s", cmd, argv[1]);
		ft_free_str_arr(paths);
		if (execve(cmd, argv, shell->env))
			perror("minishell: ");
		free(cmd);
		ft_free_str_arr(argv);
		exit(EXIT_SUCCESS);
	}
}
