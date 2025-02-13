#ifndef DEFINE_H
# define DEFINE_H

# define MALLOC_FAILED "Error: Malloc failed\n"
# define WHERE __FILE__":"__FUNCTION__":"__LINE__
enum e_error
{
	MALLOC_ERROR = -1,
	EXIT_SUCCESS,
	EXIT_FAILURE,
	DIRECTION,
	FC,
};

#endif