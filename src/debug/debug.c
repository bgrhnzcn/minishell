/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:23:18 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/28 16:10:34 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_str(t_string str)
{
	size_t	i;

	i = 0;
	printf("Size Without NULL: %ld\n", ft_vector_len(&str) - 1);
	printf("Size With NULL: %ld\n", ft_vector_len(&str));
	while (str[i])
	{
		printf("%c, ", str[i]);
		i++;
	}
	printf("\n");
}

void	debug_env(t_str_vec env)
{
	size_t	i;

	i = 0;
	printf("%ld\n", ft_vector_len(&env) - 1);
	while (env[i] != NULL)
	{
		printf("%ld.: %s\n", i + 1, env[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
