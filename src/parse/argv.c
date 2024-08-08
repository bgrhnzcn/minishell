/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:42:22 by buozcan           #+#    #+#             */
/*   Updated: 2024/08/08 20:17:48 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_whitespaces(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	while (temp->next != NULL)
	{
		if (temp->next->type == WHITESPACE)
			destroy_token(remove_token(token_list, temp->next));
		else
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
	argv_size = get_argv_size(token_list) + 1;
	argv = ft_calloc(argv_size, sizeof (char *));
	if (argv == NULL)
		return (NULL);
	while (counter < argv_size && temp != NULL)
	{
		if (temp->type == WORD)
		{
			argv[counter] = ft_strdup(temp->text);
			counter++;
		}
		temp = temp->next;
	}
	argv[counter] = NULL;
	return (argv);
}
