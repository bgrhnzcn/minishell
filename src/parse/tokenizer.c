/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:16 by buozcan           #+#    #+#             */
/*   Updated: 2024/07/14 09:53:08 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	token_type(char *input, int i, int input_len)
{
	if (input[i] == '\'')
		return (QUOTE);
	else if (input[i] == '\"')
		return (DOUBLE_QUOTE);
	else if (input[i] == '$')
		return (DOLLAR);
	else if (ft_strchr(g_whitespaces, input[i]))
		return (WHITESPACE);
	else if (input[i] == '|')
		return (PIPE);
	else if (input[i] == '<')
	{
		if (i + 1 < input_len && input[i + 1] == '<')
			return (HEREDOC);
		else
			return (INPUT);
	}
	else if (input[i] == '>')
	{
		if (i + 1 < input_len && input[i + 1] == '>')
			return (APPEND);
		else
			return (OUTPUT);
	}
	return (HEAD);
}

static t_token	*create_token_word(char *input, int i, int input_len)
{
	int				start_i;
	t_token_type	type;

	start_i = i;
	while (i < input_len)
	{
		type = token_type(input, i, input_len);
		if (type != HEAD)
			break ;
		i++;
	}
	return (new_token(WORD, ft_substr(input, start_i, i - start_i)));
}

static t_token	*create_token_dollar(char *input, int i, int input_len)
{
	int	start_i;

	start_i = i;
	while (i < input_len)
	{
		if ((i == start_i + 1 && !(ft_isalpha(input[i]) || input[i] == '_')))
			break ;
		if (i != start_i && !(ft_isalnum(input[i]) || input[i] == '_'))
			break ;
		i++;
	}
	return (new_token(DOLLAR, ft_substr(input, start_i, i - start_i)));
}

static t_token	*create_token_type(char *input, int i, int input_len)
{
	t_token_type	type;

	type = token_type(input, i, input_len);
	if (type == QUOTE)
		return (new_token(QUOTE, ft_substr(input, i, 1)));
	else if (type == DOUBLE_QUOTE)
		return (new_token(DOUBLE_QUOTE, ft_substr(input, i, 1)));
	else if (type == WHITESPACE)
		return (new_token(WHITESPACE, ft_substr(input, i, 1)));
	else if (type == DOLLAR)
		return (create_token_dollar(input, i, input_len));
	else if (type == PIPE)
		return (new_token(PIPE, ft_substr(input, i, 1)));
	else if (type == HEREDOC)
		return (new_token(HEREDOC, ft_substr(input, i, 2)));
	else if (type == INPUT)
		return (new_token(INPUT, ft_substr(input, i, 1)));
	else if (type == APPEND)
		return (new_token(APPEND, ft_substr(input, i, 2)));
	else if (type == OUTPUT)
		return (new_token(OUTPUT, ft_substr(input, i, 1)));
	else
		return (create_token_word(input, i, input_len));
}

t_token	*parse_input(t_token *token_list, char *input)
{
	int		i;
	int		input_len;
	t_token	*temp;

	i = 0;
	input_len = ft_strlen(input);
	while (i < input_len)
	{
		temp = create_token_type(input, i, input_len);
		if (temp == NULL)
			return (printf("Error happened while generating tokens.\n"), NULL);
		i += ft_strlen(temp->text);
		if (add_token_last(token_list, temp) == error)
			return (printf("Error happened while generating tokens.\n"), NULL);
	}
	if (add_token_last(token_list,
			new_token(TAIL, ft_strdup("newLine"))) == error)
		return (ft_putstr_fd("Error happened while generating tokens\n.",
				STDERR_FILENO), NULL);
	return (NULL);
}
