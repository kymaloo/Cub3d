/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:48:05 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 17:50:51 by trgaspar         ###   ########.fr       */
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
