/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:15:06 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/07 16:10:23 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *first, t_list *second)
{
	void	*temp;

	if (first == NULL || second == NULL)
		return ;
	temp = first->content;
	first->content = second->content;
	second->content = temp;
}
