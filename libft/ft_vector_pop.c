/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:10:04 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/30 00:21:15 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_vector_pop(void *vector, void *out)
{
	t_vector	*head;

	if (out == NULL || vector == NULL)
		return (-1);
	head = ft_vector_head(vector);
	if (head->lenght == 0)
		return (-1);
	ft_memcpy(out, &head->buffer[(head->lenght - 1) * head->type_size],
		head->type_size);
	head->lenght--;
	return (head->lenght);
}
