/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 01:49:38 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/01/30 16:48:38 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//This function uses bubble-sort for now. Comparator gives true when con1
//node bigger (define in comparator for different types) than next node.
void	ft_lstsort(t_list **list, t_bool (*comp)(void *con1, void *con2))
{
	t_list	*curr;
	int		i;
	int		size;
	int		counter;

	curr = *list;
	i = 0;
	size = ft_lstsize(*list);
	while (i < size)
	{
		curr = *list;
		counter = 0;
		while (counter < size - i - 1)
		{
			if (comp(curr->content, curr->next->content))
				ft_lstswap(curr, curr->next);
			curr = curr->next;
			counter++;
		}
		i++;
	}
}
