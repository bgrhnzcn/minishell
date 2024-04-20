/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:11:23 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/20 22:42:25 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	is_in_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (true);
		delim++;
	}
	return (false);
}

int	ft_strspn(char *str, char *accept)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (!is_in_delim(str[i], accept))
				break ;
			i++;
		}
	}
	return (i);
}

int	ft_strcspn(char *str, char *reject)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (is_in_delim(str[i], reject))
				break ;
			i++;
		}
	}
	return (i);
}

char	*ft_strpbrk(char *str, const char *accept)
{
	while (*str)
	{
		if (is_in_delim(*str, accept))
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, char *delim)
{
	
}