/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:07:12 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/24 17:52:38 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_vector_append(void *vector_adrr, void *val)
{
	t_vector	*head;

	head = ft_vector_head(*(char **)vector_adrr);
	if (head->lenght == head->buffer_size / head->type_size)
	{
		head = ft_vector_grow(vector_adrr, head, head->buffer_size);
		if (head == NULL)
			return (-1);
	}
	ft_memcpy(&head->buffer[head->lenght * head->type_size],
		val, head->type_size);
	head->lenght++;
	return (head->lenght);
}
