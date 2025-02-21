/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:09:22 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/21 15:09:23 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_status	ft_error(char *where, int line, char *msg, t_status errcode)
{
	printf(RED"\n\t%s%d: ERR: %s.\n"RESET, where, line, msg);
	return (errcode);
}
