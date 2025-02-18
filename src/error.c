#include "cub.h"

t_status	ft_error(char *where, int line, char *msg, t_status errcode)
{
	printf(RED"\n\t%s%d: ERR: %s.\n"RESET, where, line, msg);
	return (errcode);
}
