/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:01:36 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/24 18:07:57 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_string_delete(t_string *str, size_t from, size_t to)
{
	size_t	i;

	if (from > to || *str == NULL)
		return (-1);
	i = to;
	while (i > from)
	{
		ft_vector_remove(str, NULL, to);
		to--;
	}
	return (0);
}
