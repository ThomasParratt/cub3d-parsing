#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
#include "libft/include/libft.h"

typedef struct s_map
{
	char    **map; //this is a 2d array of the map part of the .cub file
 	char    *no;
    char    *so;
    char    *ea;
    char    *we;
    char    *floor;
    char    *ceiling;
}				t_map;

#endif