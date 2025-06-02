/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:39:42 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 15:23:11 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_status	ft_error(char *where, int line, char *msg, t_status errcode)
{
	printf(RED"\n\t%s%d: ERR: %s."RESET"\n", where, line, msg);
	return (errcode);
}
