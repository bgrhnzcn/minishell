/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:21:33 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/10 18:54:45 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
//First problem solve collision.
//Second problem define behavieor to same key different values.
//KVPair stack allocated and we need to make malloc and organize them,
//or add next node to kvpair itself so ve don't need second allocation
//but the as result we need to write new functions for this specific list type.
void	ft_table_insert(t_hash_table *table, void *key, void *value)
{
	size_t		hashed;
	t_kv_pair	checked_pair;

	if (key == NULL || value == NULL)
		return ;
	if (table->key_type == type_str)
	{
		hashed = ft_hash(key, ft_strlen((char *)key)) % table->table_size;
		if (table->table[hashed] == NULL)
		{
			table->table[hashed] = ft_lstnew(&(t_kv_pair){.key = key, .value = value});
			return ; 
		}
		checked_pair = *((t_kv_pair *)(table->table[hashed]->content));
		if (!ft_strncmp((char *)(checked_pair.key), (char *)key, ft_strlen((char *)key)))
			;
		else
			;
	}
	else
	{
		hashed = ft_hash(key, table->key_type) % table->table_size;
		if (table->table[hashed] == NULL)
		{
			*(t_kv_pair *)table->table[hashed]->content = (t_kv_pair){.key = key, .value = value};
			return ;
		}
		checked_pair = *((t_kv_pair *)(table->table[hashed]->content));
		if (!ft_memcmp(checked_pair.key, key, table->key_type))
			;
		else
			;
	}
}
