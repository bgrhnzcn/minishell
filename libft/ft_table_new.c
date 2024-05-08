/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_table_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:53:10 by buozcan           #+#    #+#             */
/*   Updated: 2024/05/08 17:38:24 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hash_table	*ft_table_new(size_t table_size, t_hash_type type, size_t (*hash)(void *data, size_t type))
{
	t_hash_table	*table;
	table = malloc(sizeof(t_hash_table));
	if (table == NULL)
		return (NULL);
	table->table = malloc(sizeof(t_hash_entry) * table_size);
	if (table->table == NULL)
		return (free(table), NULL);
	table->hash = hash;
	table->table_size = table_size;
	table->types = type;
	return (table);
}
