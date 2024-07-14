/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:20:29 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/14 10:51:06 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t nmemb, size_t size)
{
	void	*allocated;

	allocated = malloc(nmemb * size);
	if (allocated == NULL)
		return (NULL);
	return (allocated);
}
