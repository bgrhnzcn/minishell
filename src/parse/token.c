/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:31:46 by buozcan           #+#    #+#             */
/*   Updated: 2024/07/10 23:19:23 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, int index, char *text)
{
	t_token	*token;

	token = ft_calloc(1, sizeof (t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->index = index;
	token->text = text;
	if (token->text == NULL)
		return (free(token), NULL);
	return (token);
}

t_bool	add_token_last(t_token *tokens, t_token *token)
{
	t_token *temp;

	temp = tokens;
	if (temp == NULL || token == NULL)
		return (error);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = token;
	token->prev = temp;
	return (false);
}

void	remove_token(t_token *tokens, t_token *token)
{
	t_token	*temp;

	temp = tokens;
	while (temp->next != NULL)
	{
		if (temp->next == token)
		{
			temp->next = temp->next->next;
			temp->next->prev = temp;
		}
		temp = temp->next;
	}
	free(token);
}

void	print_tokens(t_token *token_list)
{
	t_token	*temp;
	char	token_type_str[10][20] = {"HEAD", "PIPE", "OUTPUT", "INPUT", "APPEND",
		"WORD", "HEREDOC", "QUOTE", "DOUBLE_QUOTE", "DOLLAR"};

	temp = token_list;
	while (temp != NULL)
	{
		printf(
			"[ INFO ] Token\n{\n\t.type = %s,\n\t.index = %d,\n\t.text = %s,\n\t.adress = %p,\n\t.next = %p,\n\t.prev = %p\n}\n",
			token_type_str[temp->type], temp->index, temp->text,
			temp ,temp->next, temp->prev);
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
