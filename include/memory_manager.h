/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:28:16 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/14 19:43:07 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGER_H
# define	MEMORY_MANAGER_H
# include	"error.h"
# include	"define.h"
# include	<stdlib.h>
# include	<aio.h>

// here, add the safe_allocation_functions ...

void	*safe_malloc(size_t size, char *area);
void	*safe_calloc(size_t nmeb, size_t size, char *area);

# define	MM_AREA_NAME_MAX_SIZE	64
# define	MM_AREA_NODE_CONTENT_NB	100

typedef struct s_content_node
{
	void					*content[MM_AREA_NODE_CONTENT_NB];
	struct s_content_node	*next;
} t_content_node;

typedef struct s_area_node
{
	char				area_name[MM_AREA_NAME_MAX_SIZE + 1];
	t_content_node		*area_content;
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

t_content_node	*create_content_node(t_mm *mm);
t_area_node		*create_area_node(t_mm *mm, char *new_area_name);
t_area_node		*go_to_area_name(t_mm *mm, char *area_name_to_find);

#endif