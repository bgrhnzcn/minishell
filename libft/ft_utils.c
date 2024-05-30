/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:50:51 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/30 17:21:09 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_deg_to_rad(float deg)
{
	return ((deg / 180) * PI);
}

float	ft_rad_to_deg(float rad)
{
	return (rad * (180 / PI));
}

static int	ft_get_int_value_of_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - 48);
	if (c >= 'A' && c <= 'F')
		return (c - 55);
	if (c >= 'a' && c <= 'f')
		return (c - 87);
	return (0);
}

int	ft_atoi_hex(const char *str)
{
	int	res;
	int	len;
	int	digit;

	if (str == NULL)
		return (0);
	len = ft_strlen(str) - 2;
	digit = 0;
	res = 0;
	while (len > 0)
	{
		res += ft_get_int_value_of_hex(str[len + 1]) * pow(16, digit);
		digit++;
		len--;
	}
	return (res);
}
