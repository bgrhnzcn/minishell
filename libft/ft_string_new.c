/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:38:05 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/23 13:55:21 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	ft_string_new(char *str)
{
	t_string	new;

	if (str == NULL)
		return (NULL);
	new = ft_vector_new(sizeof (char));
	if (new == NULL)
		return (NULL);
	while (*str)
	{
		ft_vector_append(&new, str);
		str++;
	}
	ft_vector_append(&new, str);
	return (new);
}
