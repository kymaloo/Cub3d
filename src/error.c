#include "cub.h"

t_status	ft_error(char *where, int line, char *msg, t_status errcode)
{
	printf(RED"\n\tERR: %s:%d: %s."RESET, where, line, msg);
	return (errcode);
}
