/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:55:15 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/12 12:27:49 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(char **env)
{
	char	*cwd;

	cwd = get_env(env, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
	}
	else
		printf("%s\n", cwd + 4);
	free(cwd);
}
