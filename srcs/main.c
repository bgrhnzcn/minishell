/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/20 22:53:56 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ALLOCATED

int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	char	*cmd;
	char	*path;
	char	*temp;
	char	*prompt;
	char	*splitted;
	//HISTORY_STATE state;

	cmd = malloc(0);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	//state.length = 0;
	rl_clear_history();
	path = NULL;
	while (ft_strncmp(cmd, "exit", 5))
	{
		free(cmd);
		path = getcwd(NULL, 0);
		temp = ft_strjoin("root@localhost:~", path);
		prompt = ft_strjoin(temp, "$");
		cmd = readline(prompt);
		add_history(cmd);
		printf("%s\n", cmd);
		splitted = strtok(cmd, " 	");
		printf("%s\n", splitted);
		printf("%s\n", cmd);
		free(path);
		free(temp);
		free(prompt);
	}
	free(cmd);
	exit(EXIT_SUCCESS);
}
