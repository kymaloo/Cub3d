/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:28:16 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/21 18:30:12 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGER_H
# define MEMORY_MANAGER_H
# include "ft_error.h"
# include "define.h"
# include "MLX42/MLX42.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <aio.h>

# define MM_AREA_NAME_MAX_SIZE	64
# define MM_INITIAL_CONTENT_NB	4
# define MM_LINKED_CONTENT_ARRAY_SIZE
# define MM_HASHMAP_NB_BUCKETS	256

// could add a bits field to figure quicker where to add new elem.

typedef void	*t_addr;

typedef	void (*t_deletion_func)(void *elem);

typedef struct s_area_create_data
{
	t_deletion_func	deletion_func;
	size_t			nb_hahsmap_buckets;
}	t_area_create_data;

typedef struct s_content_array
{
	t_addr			*content;
	bool			*bits;
	unsigned int	size;
}	t_content_array;

typedef struct s_content_hashmap
{
	t_content_array	*buckets;
	size_t			nb_buckets;
}	t_content_hashmap;

typedef struct s_area_node
{
	char				*area_name;
	t_content_hashmap	area_hashmap;
	t_deletion_func		deletion_func;
	struct s_area_node	*next;
}	t_area_node;

typedef struct s_memory_manager
{
	t_area_node		*areas;
} t_memory_manager,	t_mm;

typedef	enum e_mm_opcode
{
	CREATE,
	DESTROY,
	AREA_DELETE,
	ADD_ELEM,
	DEL_ELEM,
}	t_mm_opcode;

# define	MM_NUKE			666
# define	MM_AREA_CREATE	42

// here, add the safe_allocation_functions ...

void	*safe_malloc(char *area, size_t size);
void	*safe_calloc(char *area, size_t nmeb, size_t size);
char	*safe_strdup(char *area, const char *str);
void	safe_free(char *area, void *address);
char	*safe_get_next_line(char *area, int fd);
char	**safe_split(char *area, const char *s, char c);
char	*safe_substr(char *area, const char *str, unsigned int start, size_t len);
mlx_t	*safe_mlx_init(char *area);
char	*safe_strdup_with_calloc(char *area, char *str, int size);

// here be the memorymanager functions.
// failure results in nuclear_exit.

void	memory_manager(t_mm_opcode opcode, char *area_name, void *elem);
void	memory_manager_area_create(char *area_name, t_deletion_func	deletion_func, size_t nb_hahsmap_buckets);
void	nuclear_exit(t_status status);
#endif