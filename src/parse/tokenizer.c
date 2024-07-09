/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:16 by buozcan           #+#    #+#             */
/*   Updated: 2024/07/09 19:06:35 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_token(char *input, int i)
{
	if (input[i] == '\'')
			return (true);
	else if (input[i] == '\"')
		return (true);
	else if (input[i] == '|')
		return (true);
	else if (input[i] == '<')
			return (true);
	else if (input[i] == '>')
			return (true);
	return (false);
}

static t_token	*create_token_word(char *input, int i, int input_len)
{
	int		start_i;
	char	*temp;

	start_i = i;
	while (i < input_len)
	{
		if (is_token(input, i))
		{
			temp = ft_substr(input, start_i, i - 1);
			return (free(temp), new_token(WORD, start_i,
				ft_strtrim(temp, g_whitespaces)));
		}
		i++;
	}
	temp = ft_substr(input, start_i, i);
	return (free(temp), new_token(WORD, start_i,
		ft_strtrim(temp, g_whitespaces)));
}

static t_token	*create_token_type(char *input, int i, int input_len)
{
	if (input[i] == '\'')
			return (new_token(QUOTE, i, ft_substr(input, i, 1)));
	else if (input[i] == '\"')
		return (new_token(DOUBLE_QUOTE, i, ft_substr(input, i, 1)));
	else if (input[i] == '|')
		return (new_token(PIPE, i, ft_substr(input, i, 1)));
	else if (input[i] == '<')
	{
		if (i + 1 < input_len && input[i + 1] == '<')
			return (new_token(HEREDOC, i, ft_substr(input, i, 2)));
		else
			return (new_token(INPUT, i, ft_substr(input, i, 1)));
	}
	else if (input[i] == '>')
	{
		if (i + 1 < input_len && input[i + 1] == '>')
			return (new_token(APPEND, i, ft_substr(input, i, 2)));
		else
			return (new_token(OUTPUT, i, ft_substr(input, i, 1)));
	}
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
			return (ft_putstr_fd("Error happened while generating tokens.",
				STDERR_FILENO), NULL);
		i += ft_strlen(temp->text) - 1;
		if (add_token_last(token_list, temp) == error)
			return (ft_putstr_fd("Error happened while generating tokens.",
				STDERR_FILENO), NULL);
		i++;
	}
	return (NULL);
}
