/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:21:33 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/10 00:08:39 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_table_insert(t_hash_table *table, void *key, void *value)
{
	size_t		hashed;

	if (table->key_type == type_str)
	{
		hashed = ft_hash(key, ft_strlen((char *)key)) % table->table_size;
		if (!ft_memcmp(table->table[hashed].key, key, ft_strlen((char *)key)))
			table->table[hashed] = (t_kv_pair){.key = key, .value = value};
	}
	else
	{
		hashed = ft_hash(key, table->key_type) % table->table_size;
		if (!ft_memcmp(table->table[hashed].key, key, table->key_type))
			table->table[hashed] = (t_kv_pair){.key = key, .value = value};
	}
}
