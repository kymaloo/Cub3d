
#ifndef ERROR_H
# define ERROR_H

# include "define.h"
# define WHERE __FILE__":"__FUNCTION__":", __LINE__

typedef	int t_status;
t_status error(char *where, int line, char *msg, t_status errcode);

#endif