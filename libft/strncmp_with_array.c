/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp_with_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:12:37 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/28 14:32:18 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	strncmp_with_array(char *str, char **array, size_t n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] == 32 || (str[j] >= 9 && str[j] <= 13))
		j++;
	while (array[i] != NULL)
	{
		if (ft_strncmp(&str[j], array[i], n) == 0)
			return (i);
		i++;
	}
	return (-1);
}
