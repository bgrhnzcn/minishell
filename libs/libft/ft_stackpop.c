/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:12:05 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/06 17:15:49 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_stackpop(t_stack *stack)
{
	void	*content;
	t_list	*temp;

	if (stack->count == 0)
		return (ft_putstr_fd("You can't pop when stack is empty!!",
				STDERR_FILENO), NULL);
	content = stack->top->content;
	temp = stack->top;
	stack->top = stack->top->next;
	ft_lstdelone(temp, NULL);
	stack->count--;
	return (content);
}
