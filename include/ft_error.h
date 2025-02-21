#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "define.h"
# include "ainsi_color_codes.h"
# define WHERE __FILE__":", __LINE__

typedef	int t_status;

t_status ft_error(char *where, int line, char *msg, t_status errcode);

#endif