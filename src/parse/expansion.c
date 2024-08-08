/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:42:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/08 23:41:04 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_dollar2word(char **env, t_token *dollar)
{
	char	*temp;
	char	*curr_text;

	temp = get_env(env, dollar->text + 1);
	curr_text = dollar->text;
	dollar->text = ft_substr(temp, ft_strlen(curr_text),
			ft_strlen(temp) - ft_strlen(curr_text));
	if (dollar->text == NULL)
	{
		dollar->text = curr_text;
		printf("Error occured while converting dollar symbols\n");
	}
	else
		free(curr_text);
	free(temp);
	dollar->type = WORD;
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

void	perform_expansion(t_token *token_list, char **env)
{
	t_token	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type == DOLLAR)
			token_dollar2word(env, temp);
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
	char	*temp_text;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type == INPUT ||
			temp->type == APPEND ||
			temp->type == OUTPUT ||
			temp->type == HEREDOC)
		{
			temp_text = ft_strjoin(temp->text, temp->next->text);
			free(temp->text);
			temp->text = temp_text;
			destroy_token(remove_token(temp, temp->next));
		}
		temp = temp->next;
	}
}
