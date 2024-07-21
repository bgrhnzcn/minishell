/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:53:32 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/21 14:54:36 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	double_quote(t_token *tokens)
{
	t_token	*temp;
	t_token	*closing_quote;

	temp = tokens->next;
	while (temp != NULL && temp->type != DOUBLE_QUOTE)
		temp = temp->next;
	if (temp == NULL)
		return (ft_putstr_fd("Unclosed Quotes.\n", STDERR_FILENO), error);
	else
	{
		closing_quote = temp;
		temp = temp->prev;
		while (temp != tokens)
		{
			if (temp->type != DOLLAR)
				temp->type = WORD;
			temp = temp->prev;
		}
		if (tokens->next == closing_quote)
			add_token_after(tokens, new_token(WORD, ft_strdup("")));
		remove_token(tokens, closing_quote);
		remove_token(tokens, tokens);
	}
	return (false);
}

static t_bool	single_quote(t_token *tokens)
{
	t_token	*temp;
	t_token	*closing_quote;

	temp = tokens->next;
	while (temp != NULL && temp->type != QUOTE)
		temp = temp->next;
	if (temp == NULL)
		return (ft_putstr_fd("Unclosed Quotes.\n", STDERR_FILENO), error);
	else
	{
		closing_quote = temp;
		temp = temp->prev;
		while (temp != tokens)
		{
			temp->type = WORD;
			temp = temp->prev;
		}
		remove_token(tokens, closing_quote);
		remove_token(tokens, tokens);
	}
	return (false);
}

void	check_quotes(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type == DOUBLE_QUOTE)
		{
			if (double_quote(temp) == error)
				return ;
			temp = token_list;
		}
		else if (temp->type == QUOTE)
		{
			if (single_quote(temp) == error)
				return ;
			temp = token_list;
		}
		temp = temp->next;
	}
}
