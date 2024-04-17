/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:23:00 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/01/22 02:28:46 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_strcheck(char *str, t_bool (*cond)(int))
{
	int	i;

	i = 0;
	while (str[i])
		if (!cond(str[i++]))
			return (0);
	return (1);
}
