/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:42:22 by buozcan           #+#    #+#             */
/*   Updated: 2024/08/24 15:27:18 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_whitespaces(t_token *token_list)
{
	t_token	*temp;
	t_token	*place_holder;

	temp = token_list;
	while (temp != NULL)
	{
		if (temp->type == WHITESPACE)
		{
			place_holder = temp->next;
			destroy_token(remove_token(token_list, temp));
			temp = place_holder;
		}
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
	t_token	*temp2;
	char	**argv;
	int		argv_size;
	int		counter;

	temp = token_list;
	counter = 0;
	argv_size = get_argv_size(token_list) + 1;
	argv = ft_calloc(argv_size, sizeof (char *));
	while (counter < argv_size && temp != NULL)
	{
		if (temp->type == WORD)
		{
			argv[counter++] = ft_strdup(temp->text);
			temp2 = temp->next;
			destroy_token(remove_token(token_list, temp));
			temp = temp2;
			continue ;
		}
		temp = temp->next;
	}
	argv[counter] = NULL;
	return (argv);
}
