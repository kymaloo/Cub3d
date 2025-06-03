
#include "cub.h"
#include "parsing_interns.h"

int	open_map(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: The map isn't open\n");
		return (-1);
	}
	return (fd);
}

int	close_map(int fd)
{
	close(fd);
	if (fd == -1)
	{
		printf("Error: The map isn't close\n");
		return (-1);
	}
	return (EXIT_SUCCESS);
}
