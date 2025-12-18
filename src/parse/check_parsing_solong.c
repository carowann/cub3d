/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_solong.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:05:52 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/26 17:25:56 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	ff_check(t_mlx_win *window)
{
	char	**copy;

	copy = mat_copy(window->map.map_mat, window->size.y);
	if (!copy)
		return (0);
	floodfill(window, copy, window->map.player);
	ft_free_matrix(copy);
	if (window->map.ff_exit != 1)
		return (0);
	return (1);
}

void	map_checks(t_map *window, int rows, int cols)
{
	rows = window->size.y;
	cols = window->size.x;
	if (check_lines(rows, cols, window->map.map_mat) == 0) // LINES
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
	if (check_elements(rows, cols, window) == 0) // ELEMENTS
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
	if (count_elements(rows, cols, window->map.map_mat, 'P') != 1) // RED?
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
	if (!ff_check(window)) // FLOODFILL CHECK
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_MAP_FAIL);
}

int	check_lines(int rows, int cols, char **map_mat)//2
{
	int	i;
	int	row_len;

	i = 0;
	if (rows <= 3 || cols <= 3)
	{
		return (ft_printf("Map too small, wrong vibes\n", 2), 0);
	}
	while (i < rows)
	{
		row_len = ft_strlen(map_mat[i]);
		if (cols != row_len)
		{
			return (ft_printf("different lines, wrong vibes\n", 2), 0);
		}
		i++;
	}
	return (1);
}



int	count_elements(int rows, int cols, char **map, char to_check)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == to_check)
			{
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	check_elements(int rows, int cols, t_mlx_win *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->map.map_mat;
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (map[i][j] != 'C' && map[i][j] != 'E' && map[i][j] != 'P'
			&& map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N')
				return (0);
			if (map[i][j] == 'P')
				game->map.player = (t_coord){j, i};
			if (map[i][j] == 'E')
				game->map.exit = (t_coord){j, i};
		}
	}
	return (1);
}