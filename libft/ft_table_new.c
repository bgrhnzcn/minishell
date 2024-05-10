/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:53:10 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/10 18:55:01 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


//make sure everything is up to date.
t_hash_table	*ft_table_new(size_t table_size, t_types key_type,
	t_types value_type, size_t (hash)(void *data, size_t size))
{
	t_hash_table	*table;
	table = malloc(sizeof(t_hash_table));
	if (table == NULL)
		return (NULL);
	table->table = ft_calloc(table_size, sizeof(t_list *));
	if (table->table == NULL)
		return (free(table), NULL);
	table->key_type = key_type;
	table->value_type = value_type;
	table->table_size = table_size;
	table->hash = hash;
	return (table);
}
