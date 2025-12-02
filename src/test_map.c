/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:43:20 by cwannhed          #+#    #+#             */
/*   Updated: 2025/12/02 11:07:28 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Sets player direction and camera plane based on orientation character.
** N = North (facing up), S = South (facing down),
** E = East (facing right), W = West (facing left)
**
** Direction vector: where the player is looking
** Plane vector: defines the camera's field of view (FOV)
** - Perpendicular to direction
** - Length determines FOV width (0.66 gives ~66 degree FOV)
*/
static void	set_player_orientation(t_player *player, char orientation)
{
	if (orientation == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;  // Facing up
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (orientation == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;   // Facing down
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (orientation == 'E')
	{
		player->dir_x = 1.0;   // Facing right
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (orientation == 'W')
	{
		player->dir_x = -1.0;  // Facing left
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

/*
** Processes a single character from the map during parsing.
** - Digits (0-9): converted to integers for the grid
** - N/S/E/W: player spawn position, stored as walkable (0) in grid
** - Space or unknown: treated as walkable (0)
**
** Returns: the grid value for this position
*/
static int	process_map_char(char c, t_data *data, int i, int j)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		// Player spawn position found
		// Add 0.5 to center player in the grid square
		data->player->x = j + 0.5;
		data->player->y = i + 0.5;
		set_player_orientation(data->player, c);
		return (0);  // Player position is walkable
	}
	else
		return (0);  // Spaces or unknown chars = walkable
}

/*
** Reads map dimensions (first pass through file).
** Counts total lines (height) and finds maximum line length (width).
** Handles lines of different lengths for non-rectangular maps.
*/
static void	read_map_dimensions(int fd, t_data *data)
{
	char	*line;
	int		len;
	int		max_width;

	data->map->height = 0;
	max_width = 0;
	while ((line = get_next_line(fd)))
	{
		len = ft_strlen(line);
		// Remove newline if present
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		data->map->height++;
		free(line);
	}
	data->map->width = max_width;
}

/*
** Fills a single row of the map grid from a line string.
** Processes each character and pads shorter lines with 0s.
*/
static void	fill_map_row(char *line, t_data *data, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(line);
	data->map->grid[i] = ft_calloc(data->map->width + 1, sizeof(int));
	if (!data->map->grid[i])
		cleanup_and_exit(data, EXIT_FAILURE, NULL);
	// Process each character in the line
	while (j < len && line[j] != '\n')
	{
		data->map->grid[i][j] = process_map_char(line[j], data, i, j);
		j++;
	}
	// Pad with 0s for non-rectangular maps (shorter lines)
	while (j < data->map->width)
	{
		data->map->grid[i][j] = 0;
		j++;
	}
}

/*
** Reads and stores the map grid (second pass through file).
** Allocates memory for the grid and fills it row by row.
*/
static void	read_map_grid(int fd, t_data *data)
{
	char	*line;
	int		i;

	data->map->grid = ft_calloc(data->map->height + 1, sizeof(int *));
	if (!data->map->grid)
		cleanup_and_exit(data, EXIT_FAILURE, NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		fill_map_row(line, data, i);
		free(line);
		i++;
	}
}

/*
** Loads test map from file and initializes player position.
** Reads the file twice:
** 1. First pass: calculate width and height
** 2. Second pass: read and store the actual map data
**
** Also detects player spawn position (N/S/E/W) and sets orientation.
** Non-rectangular maps are supported with automatic padding.
*/
void	test_map(t_data *data)
{
	int	fd;

	// First pass: get dimensions
	fd = open("maps/test.cub", O_RDONLY);
	if (fd < 0)
		cleanup_and_exit(data, EXIT_FAILURE, "Error\nFailed to open test map\n");
	read_map_dimensions(fd, data);
	close(fd);
	// Second pass: read and store map
	fd = open("maps/test.cub", O_RDONLY);
	if (fd < 0)
		cleanup_and_exit(data, EXIT_FAILURE, "Error\nFailed to reopen test map\n");
	read_map_grid(fd, data);
	close(fd);
	// Set colors
	data->map->ceiling_color = 0x87CEEB; // Sky blue
	data->map->floor_color = 0x228B22;   // Forest green
}
