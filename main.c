/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:42:37 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/26 17:46:37 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// need malloc protections

static void free_2d(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

static void print_2d(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        ft_putstr_fd(arr[i], 1);
        i++;
    }
}

static int identify_line(char *line)
{
    if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2) ||
            !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
    {
        //ft_putendl_fd("Type identifier found", 1);
        return (0);
    }
    else if (!ft_strncmp(line, "\n", 1)) // or all whitespace
    {
        //ft_putendl_fd("Empty line", 1);
        return (1);
    }
    else // need a validity check before putting into 2d array
        return (2);
}

static int file_to_map(t_map *map, int i, char *line)
{
    char    **arr;

    if (identify_line(line) == 2)
    {
        map->map[i] = ft_strdup(line);
        i++;
    }
    else if (identify_line(line) == 0)
    {
        arr = ft_split(line, ' '); //should it be just space or whitespace also?
        if (!ft_strncmp(arr[0], "NO", 2))
            map->no = ft_strdup(arr[1]);
        if (!ft_strncmp(arr[0], "SO", 2))
            map->so = ft_strdup(arr[1]);
        if (!ft_strncmp(arr[0], "EA", 2))
            map->ea = ft_strdup(arr[1]);
        if (!ft_strncmp(arr[0], "WE", 2))
            map->we = ft_strdup(arr[1]);
        if (!ft_strncmp(arr[0], "F", 1)) // do these need to be atoied?
            map->floor = ft_strdup(arr[1]); 
        if (!ft_strncmp(arr[0], "C", 2)) // do these need to be atoied?
            map->ceiling = ft_strdup(arr[1]);
    }
    return (i);
}

static void set_map(char *arg, int lines, t_map *map)
{
    int     fd;
    char    *line;
    int     i;
    
    map->map = malloc((lines * sizeof(char *)) + 1);
    fd = open(arg, O_RDONLY);
    i = 0;
    line = get_next_line(fd);
    i = file_to_map(map, i, line);
    //ft_putstr_fd(map->map[i], 1);
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        if (!line)
            break ;
        i = file_to_map(map, i, line);
        //ft_putstr_fd(map->map[i], 1);
    }
    map->map[i] = NULL;
    close(fd);
}

// static char *get_texture()
// {
    
// }

static int  get_map_lines(char *arg)
{
    int     fd;
    char    *line;
    int     map_lines;
    
    fd = open(arg, O_RDONLY);
    line = get_next_line(fd);
    map_lines = 0;
    if (identify_line(line) == 2)
        map_lines++;
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        if (!line)
            break ;
        if (identify_line(line) == 2)
            map_lines++;
    }
    close(fd);
    return (map_lines);
}

static int  check_file_extension(char *arg)
{
    char    *ext;
    
    ext = ft_strchr(arg, '.');
    if (ext == NULL || ft_strncmp(ext, ".cub", 5))
    {
        ft_putendl_fd("Wrong file extension", 2);
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    int     map_lines;
    t_map   map;
    
    if (argc == 2)
    {
        if (check_file_extension(argv[1]))
            return (1);
        map_lines = get_map_lines(argv[1]);
        //ft_printf("map lines = %d\n", map_lines);
        set_map(argv[1], map_lines, &map);
        print_2d(map.map);
        
        free_2d(map.map);
    }
    else
        ft_putendl_fd("Incorrect number of arguments", 2);
    return (0);
}
