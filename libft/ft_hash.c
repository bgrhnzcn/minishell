/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:06:51 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/08 15:08:17 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_pow(int base, uint32_t power)
{
	while (power > 1)
	{
		base *= base;
		power--;
	}
	return base;
}

size_t	ft_hash(void *data, size_t type)
{
	uint32_t	i;
	uint32_t	res;

	i = 0;
	res = 0;
	while (i < type)
	{
		res += (*(char *)(data + i) * ft_pow(31, type - i));
		i++;
	}
	return (res);
}
