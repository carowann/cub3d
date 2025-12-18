/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giorgia <giorgia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:01:42 by giomastr          #+#    #+#             */
/*   Updated: 2025/12/02 20:11:12 by giorgia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ONLY maze map part

#include "../includes/cub3d.h"

// Requires passing integer coordinates (x, y) and map dimensions (max_x, max_y)
int	maze_fill(char **map, int x, int y, int max_x, int max_y)
{
	if (x < 0 || y < 0 || x >= max_x || y >= max_y)
		return (0); // out of bound

	char pos = map[y][x];
	if (pos == '1' || pos == 'V')
		return (1); // visiting ALL spaces
	if (pos == ' ')
		return (print_err_mess(MSG_MAP_FAIL), 2); // leaked space
	map[y][x] = 'V'; // Visited
	if (!maze_fill(map, x, y - 1, max_x, max_y)) // North
		return (0);
	if (!maze_fill(map, x, y + 1, max_x, max_y)) // South
		return (0);
	if (!maze_fill(map, x - 1, y, max_x, max_y)) // West
		return (0);
	if (!maze_fill(map, x + 1, y, max_x, max_y)) // East
		return (0);
	return (1); // Success
}



// void	map_health(t_map *window, int rows, int cols)
// {
// 	rows = window->size.y;
// 	cols = window->size.x;
// 	if (check_lines(rows, cols, window->map.map_mat) == 0) // LINES
// 		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
// 	if (check_elements(rows, cols, window) == 0) // ELEMENTS
// 		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
// 	if (count_elements(rows, cols, window->map.map_mat, 'P') != 1) // RED?
// 		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
// 	if (!ff_check(window)) // FLOODFILL CHECK
// 		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
// }

int	check_lines(int rows, int cols, char **map_mat)// do padding thing with empty spaces?
{
	int	i;
	int	row_len;

	i = 0;
	if (rows <= 3 || cols <= 3)
	{
		return (print_err_mess(MSG_MAP_FAIL), 0);
	}
	while (i < rows)
	{
		row_len = ft_strlen(map_mat[i]);
		if (cols != row_len)
		{
			return (print_err_mess(MSG_MAP_FAIL), 0);
		}
		i++;
	}
	return (1);
}
