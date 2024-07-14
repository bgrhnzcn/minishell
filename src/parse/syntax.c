/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:17:46 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/14 09:48:33 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_end_operation(t_token_type type)
{
	if (type == OUTPUT || type == APPEND || type == INPUT || type == PIPE
		|| type == HEREDOC || type == TAIL)
		return (true);
	return (false);
}

static t_bool	check_pipe(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type != PIPE
			&& temp->type != WHITESPACE
			&& temp->type != HEAD)
			break ;
		temp = temp->prev;
	}
	if (temp == NULL)
		return (printf("syntax error near unexpected token '|'\n"), error);
	temp = token_list->next;
	while (temp != NULL)
	{
		if (temp->type != PIPE
			&& temp->type != TAIL
			&& temp->type != WHITESPACE)
			return (true);
		temp = temp->next;
	}
	return (printf("syntax error near unexpected token '|'\n"), error);
}

static t_bool	check_redirections_hlpr2(t_token *temp,
	t_token_type operator, char **env)
{
	char	*var;

	if (temp->type == DOLLAR && operator != HEREDOC)
	{
		var = get_env(env, temp->text + 1);
		if (var[0] == 0)
		{
			free(var);
			return (printf("%s: ambiguous redirect\n", temp->text), error);
		}
	}
	return (true);
}

static t_bool	check_redirections(t_token *token_list, char **env)
{
	t_token	*temp;

	temp = token_list->next;
	while (temp != NULL)
	{
		if (temp->type == DOLLAR || temp->type == WORD)
		{
			if (check_redirections_hlpr2(temp, token_list->type, env) == error)
				return (error);
			while (temp->type == DOLLAR || temp->type == WORD)
			{
				if (token_list->type == HEREDOC)
					temp->type = WORD;
				temp = temp->next;
			}
			return (true);
		}
		if (is_end_operation(temp->type))
			return (printf("syntax error near unexpected token '%s'\n",
					temp->text), error);
		temp = temp->next;
	}
	return (true);
}

t_bool	check_syntax(t_token *token_list, char **env)
{
	t_token	*temp;

	temp = token_list->next;
	while (temp != NULL)
	{
		if ((is_end_operation(temp->type)
				&& temp->type != PIPE
				&& temp->type != TAIL)
			&& check_redirections(temp, env) == error)
			return (error);
		if (temp->type == PIPE && check_pipe(temp) == error)
			return (error);
		temp = temp->next;
	}
	return (true);
}
