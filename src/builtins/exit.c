/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:35:55 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/06 22:38:27 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_shell *shell, int status)
{
	if (shell->env)
		ft_free_str_arr(shell->env);
	if (shell->input)
		free(shell->input);
	exit(status);
}
