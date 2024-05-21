/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:13:02 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/22 00:37:31 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path)
{
	char	*home;

	//default path
	if (path == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
			printf("minishell: cd: HOME not set\n");
		if (chdir(home))
			printf("minishell: cd: %s: %s\n", home, strerror(errno));
	}
	//absolute path
	else if (path[0] == '/')
	{
		if (chdir(path))
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
	}
	else if (chdir(path))
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
}
