/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:55:24 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/29 19:10:59 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// Open the .cub file.

// Loop: read each line using get_next_line().

// Trim newline (\n).

// If we haven’t reached the map yet:

// If line starts with NO, SO, EA, WE, F, C, → store texture/colors later

// Else if the line looks like a map (starts with '0', '1', or spaces then '0'/'1') → map starts

// Else skip empty lines

// If map has started:

// Save each line into a dynamic array (don’t validate yet).

// If a non-map line appears after the map → error.

// Stop reading.

// Return the list of map lines and the parsed textures/colors.

// That’s Step 1.

#include "../includes/cub3d.h"

static int	is_cub_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) == 0)
		return (1);
	return (0);
}

int	check_input(int argc, char **argv)
{
	int		fd_map;

	if (argc != 2)
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_N_ARGS);
	if (!is_cub_file(argv[1]))
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_CUB_EXT);
	// return (0);
	fd_map = open(argv[1], O_DIRECTORY);
	if (fd_map > 0)
	{
		close(fd_map);
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_IS_DIR);
	}
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_OPEN_FAIL);
	return (fd_map); // CHECK THIS AS FROM SOLONG
}
char **add_line_to_grid(char **grid, char *line, int *current_height)
{
	char    **new_grid;
    int     h;

    h = *current_height; // don't like it like this

    // 1. Resize the array of pointers (char**) to fit one more row
    // We need space for the current 'h' lines + 1 new line + 1 NULL terminator.
    new_grid = (char **)realloc(grid, (h + 2) * sizeof(char *));

    if (!new_grid)
    {
        // Allocation failed: free the newly read line to prevent memory leak
        free(line);
        return (NULL);
    }

    // 2. Store the new line string at the current end of the array
    new_grid[h] = line;

    // 3. Set the new NULL terminator for the array
    new_grid[h + 1] = NULL;

    // 4. Update the height counter (number of rows)
    (*current_height)++;

    return (new_grid);
}

int read_cub(int fd, t_data *data)
{
    char *line;
    char **tmp_grid;

    if (fd < 0 || !data || !data->map)
        return (-1);

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (line[ft_strlen(line) - 1] == '\n') // grt rid of newline
            line[ft_strlen(line) - 1] = '\0';

        // Call the dynamic array helper
        tmp_grid = add_line_to_grid(data->map->grid, line, &data->map->height); // TODO

        if (!tmp_grid)
        {
            // Allocation failed: cleanup is handled inside add_line_to_grid for the current line,
            // but you should add a general cleanup for the 'data' structure here.
            close(fd);
            // cleanup_and_exit(data, EXIT_FAILURE, "Memory allocation failed during map read.");
            return (-1);
        }

        // IMPORTANT: Update the grid pointer to the new, potentially reallocated address
        data->map->grid = tmp_grid;
    }

    close(fd);

    if (data->map->height == 0)
        return (-1); // Handle empty file

    return (0);
}
