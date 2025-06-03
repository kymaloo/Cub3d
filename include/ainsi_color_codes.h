/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ainsi_color_codes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:33:43 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/23 14:20:22 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AINSI_COLOR_CODES_H
# define AINSI_COLOR_CODES_H

// Text color codes
# define RESET       "\033[0m"
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// Bold text color codes
# define BBLACK      "\033[1;30m"
# define BRED        "\033[1;31m"
# define BGREEN      "\033[1;32m"
# define BYELLOW     "\033[1;33m"
# define BBLUE       "\033[1;34m"
# define BMAGENTA    "\033[1;35m"
# define BCYAN       "\033[1;36m"
# define BWHITE      "\033[1;37m"


// Standard Background Colors
#define BGBLACK     "\033[40m"
#define BGRED       "\033[41m"
#define BGGREEN     "\033[42m"
#define BGYELLOW    "\033[43m"
#define BGBLUE      "\033[44m"
#define BGMAGENTA   "\033[45m"
#define BGCYAN      "\033[46m"
#define BGWHITE     "\033[47m"

// Bright Background Colors (if supported)
#define BGBBLACK   "\033[100m"
#define BGBRED     "\033[101m"
#define BGBGREEN   "\033[102m"
#define BGBYELLOW  "\033[103m"
#define BGBBLUE    "\033[104m"
#define BGBMAGENTA "\033[105m"
#define BGBCYAN    "\033[106m"
#define BGBWHITE   "\033[107m"

// Reset Background Only
#define BGRESET  "\033[49m"

// Reset Bold (and other intensity/weight styles)
#define BRESET      "\033[22m"

// Full Reset (attributes + colors)
#define RESET_ALL         "\033[0m"


#endif