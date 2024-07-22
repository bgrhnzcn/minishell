/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:31:46 by buozcan           #+#    #+#             */
/*   Updated: 2024/07/22 14:53:26 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *text)
{
	t_token	*token;

	token = ft_calloc(1, sizeof (t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->text = text;
	token->next = NULL;
	if (token->text == NULL)
		return (free(token), NULL);
	return (token);
}

t_token	*remove_token(t_token *tokens, t_token *token)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		if (temp == token)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			break ;
		}
		temp = temp->next;
	}
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	destroy_token(t_token *token)
{
	free(token->text);
	free(token);
}

void	print_token(t_token *token)
{
	printf(
			"[ INFO ] Token\n{\n\t.type = %s,\n\t.text = %s,\n\t.adress = %p,\n\t.next = %p,\n\t.prev = %p\n}\n",
			g_token_type_str[token->type],
			token->text,
			token,
			token->next,
			token->prev
			);
}

void	print_tokens(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		print_token(temp);
		temp = temp->next;
	}
}

void	clear_tokens(t_token *token_list)
{
	t_token	*token;
	t_token	*temp;

	token = token_list->next;
	while (token != NULL)
	{
		temp = token->next;
		free(token->text);
		free(token);
		token = temp;
	}
	token_list->next = NULL;
}
