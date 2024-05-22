/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_cat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:14:37 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/23 01:06:28 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_string_cat(t_string *dst, char *src)
{
	if (dst == NULL || src == NULL)
		return (0);
	while (*src)
	{
		ft_vector_append(dst, src);
		src++;
	}
	return (ft_vector_len(dst));
}
