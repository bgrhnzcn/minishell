/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:10:04 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/07 14:18:34 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_vector_pop(void *vector_adrr, void *out)
{
	t_vector	*head;

	if (out == NULL || vector_adrr == NULL)
		return (-1);
	head = ft_vector_head(*(char **)vector_adrr);
	if (head->lenght == 0)
		return (-1);
	if (out != NULL)
		ft_memcpy(out, &head->buffer[(head->lenght - 1) * head->type_size],
			head->type_size);
	head->lenght--;
	if (head->buffer_size > head->type_size)
	{
		if (head->lenght * head->type_size == head->buffer_size / 2)
		{
			head = ft_vector_shrink(vector_adrr, head, head->buffer_size / 2);
			if (head == NULL)
				return (-1);
		}
	}
	return (head->lenght);
}
