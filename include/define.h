#ifndef DEFINE_H
# define DEFINE_H

# define MALLOC_FAILED		"Error: Malloc failed\n"
# define ZONE_1				"petit_chacalot"
# define ZONE_PARSING_TMP	"bonjour"

# define WIDTH				3840
# define HEIGHT				2160

enum e_error
{
	MALLOC_ERROR = -1,
	EXIT_SUCCESS,
	EXIT_FAILURE,
	DIRECTION,
	FC,
};

#endif