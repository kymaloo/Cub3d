/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:28:16 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/16 22:37:58 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGER_H
# define	MEMORY_MANAGER_H
# include	"error.h"
# include	"define.h"
# include	<stdbool.h>
# include	<stdlib.h>
# include	<aio.h>

// here, add the safe_allocation_functions ...

void	*safe_malloc(size_t size, char *area);
void	*safe_calloc(size_t nmeb, size_t size, char *area);

# define	MM_AREA_NAME_MAX_SIZE	64
# define	MM_INITIAL_CONTENT_NB	4
# define	MM_HASHMAP_NB_BUCKETS	256


// could add a bits field to figure quicker where to add new elem.

typedef void *t_addr;
typedef struct s_content_array
{
	t_addr			*content;
	bool			*bits;
	unsigned int	bitfield_size;
} t_content_array;

typedef struct	s_content_hashmap
{
	t_content_array	buckets[MM_HASHMAP_NB_BUCKETS];
} t_content_hashmap;

typedef struct s_area_node
{
	char				*area_name;
	t_content_hashmap	area_hashmap;
	struct s_area_node	*next;
} t_area_node;

typedef struct s_memory_manager
{
	t_area_node		*areas;
} t_memory_manager, t_mm;


// here be the memorymanager functions.
// failure results in nuclear_exit.

t_mm 	*mm_create(void);
void	mm_destroy(t_mm *mm);

void	mm_area_create(t_mm *mm, char *area_name);
void	mm_area_delete(t_mm *mm, char *area_name);

void	mm_area_add_elem(t_mm *mm, char *area, void *elem);
void	mm_area_free_elem(t_mm *mm, char *area, void *elem);

void	mm_nuclear_exit(t_mm *mm, t_status status);
#endif