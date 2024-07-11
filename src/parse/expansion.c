/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:42:59 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/11 22:35:44 by bgrhnzcn         ###   ########.fr       */
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
		remove_token(tokens, temp);
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

static int	get_argv_size(t_token *token_list)
{
	t_token	*temp;
	int		argv_size;

	temp = token_list;
	argv_size = 0;
	while (temp != NULL)
	{
		if (temp->type == WORD)
			argv_size++;
		temp = temp->next;
	}
	return (argv_size);
}

char	**create_argv(t_token *token_list)
{
	t_token	*temp;
	char	**argv;
	int		argv_size;
	int		counter;

	temp = token_list;
	counter = 0;
	argv_size = get_argv_size(token_list);
	printf("%d\n", argv_size);
	argv = malloc(argv_size * sizeof (char *));
	if (argv == NULL)
		return (NULL);
	while (counter < argv_size)
	{
		if (temp->type == WORD)
		{
			argv[counter] = temp->text;
			counter++;
		}
		temp = temp->next;
	}
	return (argv);
}