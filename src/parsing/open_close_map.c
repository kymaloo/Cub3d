/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:46 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/21 15:08:47 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

int	open_map(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: The map isn't open\n");
		return (-1);
	}
	return (fd);
}

int	close_map(int fd)
{
	close(fd);
	if (fd == -1)
	{
		printf("Error: The map isn't close\n");
		return (-1);
	}
	return (EXIT_SUCCESS);
}
