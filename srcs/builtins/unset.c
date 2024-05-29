/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:14:08 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/27 17:26:01 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_str_vec *env, t_string var)
{
	t_string	temp;
	int			i;

	i = find_env_index(*env, var);
	if (i == -1)
		return ;
	ft_vector_remove(env, &temp, i);
	ft_string_free(temp);
}
