#include "cub.h"

t_status	ft_error(char *where, int line, char *msg, t_status errcode)
{
	printf(RED"\n\t%s%d: ERR: %s."RESET, where, line, msg);
	return (errcode);
}
