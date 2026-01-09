/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:55:24 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/09 17:36:36 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// Open the .cub file.
// Loop: read each line using get_next_line().
// Trim newline (\n). - If we haven’t reached the map yet: if line starts with NO, SO, EA, WE, F, C, → store texture/colors later
// Else if the line looks like a map (starts with '0', '1', or spaces then '0'/'1') → map starts
// Else skip empty lines
// If map has started:
// Save each line into a dynamic array (don’t validate yet).
// If a non-map line appears after the map → error.
// Stop reading.
// Return the list of map lines and the parsed textures/colors.

// 1. check whether .cub file is healthy - are all elements there? Is map at the bottom?
// 2. examine identifiers and paths
// 3. parse map

#include "../../includes/cub3d.h"
#include <stdbool.h>

// TO-DO FILE CUB_UTILS
bool	line_is_empty(char *s)
{
	while (*s && ft_isspace(*s))
		return (true);
	return (false);
}

bool	line_is_ids(char *s)
{
	int	id;

	id = get_id_line(s);
	if (id == -1)
		return (false);
	return (true);
}

bool	line_is_map(char *s)
{
	int	 i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] && (s[i] == '1'))
		return (true);
	return (false);
}

//pseudo - F  (r)220,(g)100, (b)0
int	validate_colours(t_data *data, char *colour) // analyse value
{
	int		r;
	int		g;
	int		b;
	int		row_count;
	char	**value;

	value = ft_split(colour, ',');
	if (!value)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	row_count = 0;
	while (value[row_count] != NULL)
		row_count++;
	if (row_count != 3)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_COL_FAIL);
	r = ft_atoi(value[0]);
	g = ft_atoi(value[1]);
	b = ft_atoi(value[2]);
	if (r < 0 || r > 255 || (g < 0 || g > 255) || (b < 0 || b > 255))
		cleanup_and_exit(data, EXIT_FAILURE, MSG_COL_FAIL);
	return ((r << 16) | (g << 8) | b);
}

char 	*clean_path(t_data *data, char *s)
{
	int i;
	char *path;

	i = 2;
	while (s[i] && ft_isspace(s[i]))
		i++;
	path = ft_strdup(&s[i]);
	if (!path)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	return (path);
}

void    read_ids(t_data *data, char *line)
{
	if (line && ft_strncmp(line, "NO", 2) == 0)
		data->textures_path[NORTH] = clean_path(data, line);
	else if (line && ft_strncmp(line, "SO", 2) == 0)
		data->textures_path[SOUTH] = clean_path(data, line);
	else if (line && ft_strncmp(line, "WE", 2) == 0)
		data->textures_path[WEST] = clean_path(data, line);
	else if (line && ft_strncmp(line, "EA", 2) == 0)
		data->textures_path[EAST] = clean_path(data, line);
	else if (line && ft_strncmp(line, "F", 1) == 0)
		data->map->floor_color = validate_colours(data, line);
	else if (line && ft_strncmp(line, "C", 1) == 0)
		data->map->ceiling_color = validate_colours(data, line);
	else
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL);
	return ;
}

void    read_cub(t_data *data, int fd)
{
	char *line;
	int id;

	line = 0;
	if (fd < 0 || !data || !data->map)
		return ;
	id =  0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_is_empty(line) && id < 6)
		{
			free(line);
			continue ;
		}
		if (id < 6 && line_is_ids(line))
		{
			read_ids(data, line);
			id++;
		}
		else if (id == 6 && line_is_map(line))
			add_line(line, data);
		free(line);
	}
	allocate_map(data, data->map->lines);
	// print_map_debug(data);
	close(fd);
}
