#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
#include "libft/include/libft.h"

// typedef struct s_textures
// {
// 	char    *no_path;
//     char    *so_path;
//     char    *ea_path;
//     char    *we_path;
//     char    *floor;
//     char    *ceiling;
// }				t_textures;

typedef struct s_map
{
	char    **map; //this is a 2d array of the map part of the .cub file
}				t_map;

#endif