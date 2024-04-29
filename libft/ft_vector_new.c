/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:01:32 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/29 20:09:36 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vector_new(size_t type_size_b)
{
	t_vector	*vector;

	vector = ft_calloc(1, (sizeof(t_vector) + (type_size_b * 1)));
	if (vector == NULL)
		return (NULL);
	vector->type_size = type_size_b;
	vector->lenght = 0;
	vector->buffer_size = type_size_b * 1;
	return (&vector->buffer);
}
