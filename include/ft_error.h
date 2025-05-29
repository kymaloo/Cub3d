/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:31:00 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 13:47:50 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "define.h"
# include "ainsi_color_codes.h"

typedef int	t_status;

t_status	ft_error(char *where, int line, char *msg, t_status errcode);

#endif