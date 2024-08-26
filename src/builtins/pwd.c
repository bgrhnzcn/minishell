/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:55:15 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/26 16:06:23 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(char **env)
{
	char	*cwd;

	cwd = get_env(env, "PWD");
	if (ft_strequ(cwd, ""))
	{
		free(cwd);
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
	}
	else
		printf("%s\n", cwd + 4);
	free(cwd);
}
