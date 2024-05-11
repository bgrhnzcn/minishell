/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:27:34 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/11 16:38:15 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	ft_table_print(t_hash_table *table)
{
	size_t		i;
	t_kv_pair	*temp;

	i = 0;
	while (i < table->table_size)
	{
		printf("%zu: ", i);
		temp = &table->table[i];
		while (temp != NULL)
		{
			if (temp->value == NULL)
				printf("key:%s, val:(null) --->", (char *)temp->key);
			else
				printf("key:%s, val:%d --->", (char *)temp->key, *(int*)temp->value);
			temp = temp->next;
		}
		printf("\n");
		i++;
	}
}
