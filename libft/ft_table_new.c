/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:53:10 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/10 00:15:59 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hash_table	*ft_table_new(size_t table_size, t_types key_type,
	t_types value_type, size_t (hash)(void *data, size_t size))
{
	t_hash_table	*table;
	table = malloc(sizeof(t_hash_table));
	if (table == NULL)
		return (NULL);
	table->table = malloc(sizeof(t_kv_pair) * table_size);
	if (table->table == NULL)
		return (free(table), NULL);
	table->key_type = key_type;
	table->value_type = value_type;
	table->table_size = table_size;
	table->hash = hash;
	return (table);
}
