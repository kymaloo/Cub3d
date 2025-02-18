/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_hashmap_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:16:23 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/18 12:11:04 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_interns.h"

/**
 * @brief multiplies ptr by 2^64 / phi  (golden ratio)
 * then keeps only the top bits of the 64-bit hash, which are better mixed.
 *  >> (64 - log2(nb_buckets should keep it under the nb of buckets))
 * 
 * @param ptr 
 * @return size_t 
 */
size_t	mm_hashmap_hash(void *ptr)
{
	size_t addr;
	size_t hash;
	unsigned long long fibonnacci_ratio;

	fibonnacci_ratio = 11400714819323198485ull;
	addr = (size_t) ptr;
	hash = (addr * fibonnacci_ratio) >> (64 - (int) log2(MM_HASHMAP_NB_BUCKETS)); //TODO REQUIRES METH.H
	return (hash % MM_HASHMAP_NB_BUCKETS);
}


void	mm_hashmap_add(t_mm *mm, t_content_hashmap *hashmap, void *elem)
{
	size_t hash;
	size_t where;

	hash = mm_hashmap_hash(elem);
	where = findFirstZeroBit(hashmap->buckets[hash].bits, hashmap->buckets[hash].size);
	if (where == (size_t) -1)
	{
		where = hashmap->buckets[hash].size + 1;
		upgrade_content_array_size(mm, &hashmap->buckets[hash]);
	}
	hashmap->buckets[hash].content[where] = elem;
	hashmap->buckets[hash].bits[where] = 1;
	return ;
}

void	mm_hashmap_remove(t_mm *mm, t_content_hashmap *hashmap, void *elem)
{
	size_t			hash;
	t_content_array	*array;
	size_t			i;

	hash = mm_hashmap_hash(elem);
	array = &hashmap->buckets[hash];
	i = 0;
	while (i < array->size)
	{
		if (array->content[i] == elem)
		{
			free(elem);
			array->bits[i] = 0;
			return ;
		}
		i++;
	}
	mm_nuclear_exit(mm, ft_error(WHERE, "elem not found (how dare you give me false information)", EXIT_FAILURE));
}
