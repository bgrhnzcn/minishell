/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:55:15 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/20 17:22:14 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*cwd;

	cwd = NULL;
	printf("%s\n", getcwd(cwd, 0));
	free(cwd);
	exit(EXIT_SUCCESS);
}
