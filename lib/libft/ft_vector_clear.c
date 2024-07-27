/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:08:30 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/01 22:57:55 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_clear(void *vector_adrr)
{
	t_vector	*vector;
	int			i;

	if (vector_adrr == NULL)
		return ;
	vector = *(char **)vector_adrr;
	i = ft_vector_len(vector);
	while (i > 0)
	{
		ft_vector_pop(vector_adrr, NULL);
		i--;
	}
}
