/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:22:17 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/30 01:23:10 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	*ft_vector_realloc(void	*vector_adrr, t_vector *head)
{
	t_vector	*new_vector;

	new_vector = malloc(sizeof (t_vector) + (head->buffer_size * 2));
	if (new_vector == NULL)
		return (NULL);
	ft_memmove(&new_vector->buffer, head->buffer, head->buffer_size);
	new_vector->buffer_size = head->buffer_size * 2;
	new_vector->type_size = head->type_size;
	new_vector->lenght = head->lenght;
	ft_vector_free(*(char **)vector_adrr);
	head = new_vector;
	*((char **)vector_adrr) = head->buffer;
	return (head);
}
