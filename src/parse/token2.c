/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:50:22 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/24 17:42:17 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	add_token_after(t_token *before, t_token *new)
{
	if (before == NULL || new == NULL)
		return (error);
	new->next = before->next;
	before->next = new;
	new->next->prev = new;
	new->prev = before;
	return (true);
}

t_token	*remove_sublist(t_token *list_start, t_token *list_end)
{
	t_token	*sub_list;

	sub_list = new_token(HEAD, ft_strdup(""));
	if (sub_list == NULL)
		return (printf("Error occured while creating command list.\n"), NULL);
	list_start->prev->next = list_end->next;
	list_end->next->prev = list_start->prev;
	list_start->prev = sub_list;
	sub_list->next = list_start;
	list_end->next = NULL;
	if (add_token_last(sub_list, new_token(TAIL, ft_strdup(""))))
	{
		clear_tokens(sub_list);
		return (printf("Error occured while creating command list.\n"), NULL);
	}
	return (sub_list);
}

t_bool	add_token_last(t_token *token_list, t_token *token)
{
	t_token	*temp;

	temp = token_list;
	if (temp == NULL || token == NULL)
		return (EXIT_FAILURE);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = token;
	token->prev = temp;
	return (EXIT_SUCCESS);
}
