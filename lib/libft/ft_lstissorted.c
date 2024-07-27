/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstissorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:28:01 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/01/30 17:30:52 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_lstissorted(t_list *lst, t_bool (*comp)(void *con1, void *con2))
{
	if (lst == NULL)
		return (true);
	if (comp == NULL)
		return (false);
	while (lst->next != NULL)
	{
		if (comp(lst->content, lst->next->content))
			return (false);
		lst = lst->next;
	}
	return (true);
}
