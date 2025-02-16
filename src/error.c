#include "cub.h"

void str_add(char *str_dest, char *to_add)
{
	
}

t_status error(char *where, int line, char *msg, t_status errcode)
{
	char *err_msg;
	char *the_line;

	line = itoa(line);
	err_msg = NULL;
	str_add(err_msg, RED);
	str_add(err_msg, "\tERR: ");
	str_add(err_msg, msg);
	str_add(err_msg, ":");
	str_add(err_msg, the_line);
	str_add(err_msg, "\n");
	str_add(err_msg, RESET);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	free(err_msg);
	return (errcode);
}