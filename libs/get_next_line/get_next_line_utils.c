/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:42:45 by buozcan           #+#    #+#             */
/*   Updated: 2023/11/14 20:52:12 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, char c)
{
	if (str == NULL || c == 0)
		return (NULL);
	while (*str)
		if (*str++ == c)
			return (--str);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*res;
	size_t			i;
	size_t			j;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = 0;
	}
	if (s2 == NULL)
		return (s1);
	res = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (res == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = 0;
	free(s1);
	return (res);
}
