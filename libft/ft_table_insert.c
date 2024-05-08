/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:21:33 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/08 17:28:26 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_table_insert(t_hash_table *table, void *key, void *value)
{
	size_t		hashed;
	t_hash_type	types;

	types = table->types;
	hashed = ft_hash(key, types.key_type) % table->table_size;
	if (!ft_memcmp(table->table[hashed].key, key, types.key_type))
		table->table[hashed] = (t_hash_entry){.key = key, .value = value};
}
