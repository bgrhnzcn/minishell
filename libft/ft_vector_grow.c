/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_grow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:22:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/01 01:48:03 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	*ft_vector_grow(void *vector_adrr, t_vector *head, size_t size)
{
	t_vector	*new_vector;

	new_vector = malloc(sizeof (t_vector) - 8 + head->buffer_size + size);
	if (new_vector == NULL)
		return (NULL);
	ft_memmove(&new_vector->buffer, head->buffer, head->buffer_size);
	new_vector->buffer_size = head->buffer_size + size;
	new_vector->type_size = head->type_size;
	new_vector->lenght = head->lenght;
	ft_vector_free(*(char **)vector_adrr);
	head = new_vector;
	*((char **)vector_adrr) = head->buffer;
	return (head);
}
