/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:48:05 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 18:49:08 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
