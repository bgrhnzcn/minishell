/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:13:49 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/09/24 16:44:33 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_dollar(char *env, t_token *dollar)
{
	t_token	*temp;
	char	**split;
	int		i;
	int		max;

	temp = dollar;
	env = ft_strchr(env, '=');
	if (*(env + 1) == 0)
	{
		dollar->type = WORD;
		return ;
	}
	split = ft_split(env + 1, ' ');
	max = ft_strarrlen(split);
	i = 0;
	while (split[i])
	{
		if (max > 1)
			add_token_after(temp, new_token(WHITESPACE, ft_strdup(" ")));
		add_token_after(temp, new_token(WORD, ft_strdup(split[i])));
		temp = temp->next->next;
		i++;
	}
	ft_free_str_arr(split);
}

void	create_joined_words(t_token *tokens)
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
