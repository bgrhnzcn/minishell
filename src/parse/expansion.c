/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:42:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/11 18:59:45 by bgrhnzcn         ###   ########.fr       */
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
	dollar->type = WORD;
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

void	join_cons_words(t_token *token_list)
{
	t_token	*temp;
}