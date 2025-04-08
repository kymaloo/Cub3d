#include "explosives.h"
#include <stdbool.h>
#include <string.h>


typedef struct s_target_location
{
	char	file[1024];
	int		line;
} t_target_location;

typedef struct s_c4
{
	long				countdown;
	long				target_number;
	int					skip_from;
	bool				skip;
} t_c4;

static void *play_with_detonator(size_t size, char *file, int line, const char *function, t_c4 *c4)
{
	if (c4->countdown == 0)
	{
		printf("\t%s:%-9d in %-35s: 💥 BOOM BABEEH 💥💥💥\n", file, line, function);
		return (NULL);
	}
	else if (c4->skip = true)
	{
		return (malloc(size));
	}
	else if (c4->countdown > 0)
	{
		printf("\t%s:%-9d in %-35s: countdown to midnight: %d... 💣... \n", file, line, function, c4->countdown);
		return (malloc(size));
	}
	else if (c4->target_number >= 0)
	{
		printf("\t\t%s:%-9d in %-35s:  💢(%d)💢🔭", file, line, function, c4->countdown);
		return (malloc(size));
	}
	else
	{
		printf(BMAGENTA"\t🔥🧨🚒 WHAT THE FUCK IS A KILOMETER ?!?!?!?!??/// 🔥🧨🔥🧨\n"RESET);
		return (NULL);
	}
}
//TODO 
static void	skip_the_skip(t_c4 *c4, t_target_location *last_known_location, char *file, int line, const char *function)
{
	if (last_known_location->line == line && strcmp(last_known_location->file, file) == EXIT_SUCCESS)
	{
		if (!c4->skip && c4->skip_from != -1)
		{
			printf("\t...\n");
			c4->skip_from = line;
			c4->skip = true;
		}
	}
	else //FIX ME
	{
		c4->skip_from == -1;
		c4->skip = false;
	}
	memmove(&file, &last_known_location->file, ft_strlen(file) + 1);
	if (c4->skip_from != -1 && c4->skip == false \
	&& (c4->skip_from != c4->skip_from + 1 || c4->skip_from != c4->skip_from + 2))
	{
		printf("\t%s:%-9d in %-35s: countdown to midnight: %d... 💣... \n", file, line, function, c4->countdown - c4->skip_from / 2);
		printf("\t...\n");
	}
}

void say_hewwo(t_c4	*c4)
{
	if (c4->countdown == -1 &&c4->target_number == -1)
	{
		printf(BBLUE"🐒 Hello Commander !%s%s\n\tSelect your target: 🔭🙈\n"RESET, RESET, BLUE);
		c4->target_number++;
	}
	else
	{
		printf(BLUE"info: Usage: \n\tcompile & launche with %s`-D COUNTODWN=-1`%s%s to send tactical recon team to the ennemy.\n"RESET, BBLUE, RESET, BLUE);
		c4->target_number++;
	}
}

void *explosive_malloc(size_t size, char *file, int line, const char *function)
{
	static t_target_location	last_known_location = {"nowhere",-1};
	static t_c4	c4 = {COUNTDOWN, 0, -1, false};
	void *result;

	
	say_hewwo(&c4);
	skip_the_skip(&c4, &last_known_location, file, line, function);
	return(c4.skip = false, play_with_detonator(size, file, line, function, &c4));
}
























void *explosive_calloc(size_t nmeb, size_t size, char *file, int line, const char *function)
{
	static long countdown = COUNTDOWN;
	static long target	  = -1;
	if (countdown > 0)
	{
		printf("\t%s:%-9d in %-35s: countdown to midnight: %d", file, line, function, countdown);
		return (calloc(nmeb, size));
	}
	else if (countdown == 0)
	{
		printf("\t%s:%-9d in %-35s: BOOM BABEEH %d", file, line, function, countdown);
		return (NULL);
	}
	else if (countdown == -1 && target == -1)
	{
		printf("Hello Commander\n");
		target++;
	}
	if (target >= 0)
	{
		printf("\tSelect your target: %s:%-9d in %-35s: BOOM BABEEH %d", file, line, function, countdown);
		return (calloc(nmeb, size));
	}
	printf("\t WHAT THE FUCK IS A KILOMETER ?!?!?!?!??///\n");
	return (NULL);
}