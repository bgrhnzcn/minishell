/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:06:51 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/09 23:58:37 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_pow(int base, unsigned int power)
{
	while (power > 1)
	{
		base *= base;
		power--;
	}
	return base;
}

size_t	ft_hash(void *data, size_t size)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < size)
	{
		res += (*(char *)(data + i) * ft_pow(31, size - i));
		i++;
	}
	return (res);
}
