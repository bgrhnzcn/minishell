/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:44:58 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/15 01:16:42 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buildins(t_shell *shell, char **argv)
{
	if (ft_strequ(argv[0], "exit"))
		mini_exit(shell, EXIT_SUCCESS);
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

static t_bool	search_in_path(char *path, char *command)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(path);
	if (dir == NULL)
		return (error);
	while (dirent != NULL)
	{
		printf("%s\n", dirent->d_name);
		dirent = readdir(dir);
	}
}

void	executer(t_shell *shell, char **argv)
{
	char	**paths;
	char	*test;
	int		path_index;

	if (!buildins(shell, argv))
		return ;
	else
	{
		paths = ft_split(get_env(shell->env, "PATH"), ':');
		path_index = 0;
		while (paths[path_index] != NULL)
			search_in_path(paths[path_index++], argv[0]);
		test = ft_calloc(300, sizeof (char));
		ft_strlcat(test, argv[0], 300);
		shell->pid = fork();
		if (shell->pid == 0)
		{
			if (execve(test, argv, shell->env))
				printf("%s: %s\n", "minishell", strerror(errno));
			ft_free_str_arr(argv);
			exit(EXIT_SUCCESS);
		}
		else
			wait(NULL);
	}
}
