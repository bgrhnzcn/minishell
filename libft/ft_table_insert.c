/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:21:33 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/11 17:14:27 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
//First problem solve collision.
//KVPair stack allocated and we need to make malloc and organize them,
//or add next node to kvpair itself so ve don't need second allocation
//but the as result we need to write new functions for this specific list type.

static void	*ft_create_entry(void *data, t_types type)
{
	void	*entry;

	entry = malloc(type);
	if (entry == NULL)
		return (NULL);
	ft_memcpy(entry, data, type);
	return (entry);
}

static void	ft_table_insert_str(t_hash_table *table,
	void *key, void *value)
{
	size_t		hashed;
	t_kv_pair	pair;
	t_kv_pair	*temp;

	hashed = ft_hash(key, ft_strlen((char *)key)) % table->table_size;
	if (table->table[hashed].is_filled == false)
	{
		table->table[hashed] = (t_kv_pair){.key = key, .value = value,
			.is_filled = true};
		return ;
	}
	pair = table->table[hashed];
	temp = &pair;
	while (temp != NULL)
	{
		if (!ft_strncmp((char *)(pair.key), (char *)key, ft_strlen((char *)key) + 1))
			//Second problem define behavieor to same key different values.
			return ;
		temp = temp->next;
	}
	temp = malloc(sizeof(t_kv_pair));
	if (temp == NULL)
		return ;
	*temp = (t_kv_pair){.key = key, .value = value, .is_filled = true};
}

static void	ft_table_insert_generic(t_hash_table *table,
	void *key, void *value)
{
	size_t		hashed;
	t_kv_pair	pair;
	t_kv_pair	*temp;

	hashed = ft_hash(key, table->key_type) % table->table_size;
	if (table->table[hashed].is_filled == false)
	{
		table->table[hashed].key = 
		table->table[hashed] = (t_kv_pair){.key = key, .value = value,
			.is_filled = true};
		return ;
	}
	pair = table->table[hashed];
	temp = &pair;
	while (temp != NULL)
	{
		if (!ft_memcmp(temp->key, key, table->key_type))
			//Second problem define behavieor to same key different values.
			return ;
		temp = temp->next;
	}
	temp = malloc(sizeof(t_kv_pair));
	if (temp == NULL)
		return ;
	*temp = (t_kv_pair){.key = key, .value = value, .is_filled = true};
}

void	ft_table_insert(t_hash_table *table, void *key, void *value)
{
	if (key == NULL || value == NULL)
		return ;
	if (table->key_type == type_str)
		ft_table_insert_str(table, key, value);
	else
		ft_table_insert_generic(table, key, value);
}
