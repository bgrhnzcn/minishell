/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:56:49 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/30 16:13:24 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_vector_remove(void *vector_adrr, void *out, const size_t index)
{
	t_vector	*head;

	if (out == NULL || vector_adrr == NULL)
		return (-1);
	head = ft_vector_head(*(char **)vector_adrr);
	if (head->lenght == 0)
		return (-1);
	if (out != NULL)
		ft_memcpy(out, &head->buffer[index * head->type_size],
			head->type_size);
	ft_memmove(&head->buffer[index * head->type_size],
		&head->buffer[(index + 1) * head->type_size],
		(head->lenght - index - 1) * head->type_size);
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
