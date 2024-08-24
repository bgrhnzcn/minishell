/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:42:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/24 18:21:57 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_dollar(char *env, t_token *dollar)
{
	t_token	*temp;
	char	**split;
	int		i;

	temp = dollar;
	env = ft_strchr(env, '=');
	if (env + 1 == NULL)
	{
		dollar->type = WORD;
		return ;
	}
	split = ft_split(env + 1, ' ');
	i = 0;
	while (split[i])
	{
		add_token_after(temp, new_token(WHITESPACE, ft_strdup(" ")));
		add_token_after(temp, new_token(WORD, ft_strdup(split[i])));
		temp = temp->next->next;
		i++;
	}
	ft_free_str_arr(split);
}

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
		return ;
	}
	split_dollar(temp, dollar);
	if (dollar->text == NULL)
		dollar->text = ft_strdup("");
	free(temp);
}

static void	create_joined_words(t_token *tokens)
{
	t_token	*temp;
	char	*temp_text;

	temp = tokens->next;
	while (temp->type == WORD)
	{
		temp_text = ft_strjoin(tokens->text, temp->text);
		if (temp_text == NULL)
			printf("Error encountered while word collaping.\n");
		destroy_token(remove_token(tokens, temp));
		free(tokens->text);
		tokens->text = temp_text;
		temp = tokens->next;
	}
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
		dollar->text = ft_strdup(curr_text);
	}
	else
		dollar->text = ft_strdup(temp);
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

void	join_cont_words(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type == WORD)
			create_joined_words(temp);
		temp = temp->next;
	}
}

void	merge_redirs(t_token *token_list)
{
	t_token	*temp;
	t_token	*temp2;
	char	*temp_text;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type == INPUT
			|| temp->type == APPEND
			|| temp->type == OUTPUT
			|| temp->type == HEREDOC)
		{
			temp_text = ft_strjoin(temp->text, temp->next->text);
			free(temp->text);
			temp->text = temp_text;
			temp2 = temp->next->next;
			destroy_token(remove_token(temp, temp->next));
			temp->next = temp2;
			temp2->prev = temp;
		}
		temp = temp->next;
	}
}
