/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:42:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/01 18:39:07 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_dollar2word(char **env, t_token *dollar)
{
	char	*temp;

	if (ft_strequ(dollar->text, "$"))
	{
		dollar->type = WORD;
		return ;
	}
	temp = get_env(env, dollar->text + 1);
	if (ft_strequ(temp, ""))
	{
		dollar->type = WHITESPACE;
		free(temp);
		return ;
	}
	split_dollar(temp, dollar);
	if (dollar->text == NULL)
		dollar->text = ft_strdup("");
	free(temp);
}

static t_bool	token_dollar2exitcode(t_token *dollar)
{
	if (ft_strequ(dollar->text + 1, "?"))
	{
		free(dollar->text);
		dollar->type = WORD;
		dollar->text = ft_itoa(g_global_exit);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void	token_quoted_dollar2word(char **env, t_token *dollar)
{
	char	*temp;
	char	*curr_text;

	if (ft_strequ(dollar->text, "$"))
	{
		dollar->type = WORD;
		return ;
	}
	temp = get_env(env, dollar->text + 1);
	if (!ft_strequ(temp, ""))
	{
		curr_text = ft_strchr(temp, '=') + 1;
		free(dollar->text);
		dollar->text = ft_strdup(curr_text);
	}
	else
	{
		free(dollar->text);
		dollar->text = ft_strdup(temp);
	}
	free(temp);
	dollar->type = WORD;
}

void	perform_expansion(t_token *token_list, char **env)
{
	t_token	*temp;
	t_token	*place_holder;

	temp = token_list;
	while (temp != NULL)
	{
		place_holder = temp->next;
		if ((temp->type == DOLLAR || temp->type == QUOTED_DOLLAR)
			&& !token_dollar2exitcode(temp))
			continue ;
		if (temp->type == DOLLAR)
		{
			token_dollar2word(env, temp);
			if (temp->type == WORD || temp->type == WHITESPACE)
				continue ;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			destroy_token(remove_token(token_list, temp));
			temp = place_holder;
			continue ;
		}
		if (temp->type == QUOTED_DOLLAR)
			token_quoted_dollar2word(env, temp);
		temp = temp->next;
	}
}
