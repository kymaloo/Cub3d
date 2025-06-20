/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_bitfield_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:08:20 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 11:24:39 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_interns.h"

static size_t	find_zero_in_chunk(size_t chunk)
{
	size_t	j;

	j = 0;
	while (j < sizeof(size_t) * 8)
	{
		if (!(chunk & ((size_t)1 << j)))
		{
			return (j);
		}
		j++;
	}
	return ((size_t) - 1);
}

static	size_t	process_chunks(const bool *bits, size_t i, size_t length)
{
	size_t	chunk;
	size_t	j;
	size_t	bit_index;

	chunk = 0;
	j = 0;
	while (j < sizeof(size_t) * 8 && i + j < length)
	{
		chunk |= ((size_t)bits[i + j] << j);
		j++;
	}
	bit_index = find_zero_in_chunk(chunk);
	if (bit_index != (size_t)-1)
	{
		return (i + bit_index);
	}
	return ((size_t) - 1);
}

size_t	find_first_zero_bit(const bool *bits, size_t length)
{
	size_t	i;
	size_t	bit_index;

	i = 0;
	while (i + sizeof(size_t) * 8 <= length)
	{
		bit_index = process_chunks(bits, i, length);
		if (bit_index != (size_t) - 1)
		{
			return (bit_index);
		}
		i += sizeof(size_t) * 8;
	}
	while (i < length)
	{
		if (!bits[i])
		{
			return (i);
		}
		i++;
	}
	return ((size_t) - 1);
}
