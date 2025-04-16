

#ifndef EXPLOSIVES_H
# define EXPLOSIVES_H

# include <stdio.h>
# include <stdlib.h>
# include "debug.h"

# ifdef DEBUG
#  if DEBUG == EXPLOSIVES
#  define malloc(X) explosive_malloc(X, __FILE__, __LINE__, __FUNCTION__)
#  define ft_calloc(X, Y) explosive_calloc(X, Y, __FILE__, __LINE__, __FUNCTION__)
#  endif
# endif
#endif