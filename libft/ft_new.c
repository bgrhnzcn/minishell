/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:44:06 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/11 23:44:25 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_new(void *data, t_types type)
{
	void	*entry;

	entry = malloc(type);
	if (entry == NULL)
		return (NULL);
	ft_memcpy(entry, data, type);
	return (entry);
}
