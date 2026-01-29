/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:56:30 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/29 14:27:45 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_player_direction(t_data *data, char c)
{
	data->player->dir_x = 0;
	data->player->dir_y = 0;
	data->player->plane_x = 0;
	data->player->plane_y = 0;
	if (c == 'N')
	{
		data->player->dir_y = -1.0;
		data->player->plane_x = 0.66;
	}
	else if (c == 'S')
	{
		data->player->dir_y = 1.0;
		data->player->plane_x = -0.66;
	}
	else if (c == 'E')
	{
		data->player->dir_x = 1.0;
		data->player->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		data->player->dir_x = -1.0;
		data->player->plane_y = -0.66;
	}
}

char	**copy_matrix(char **grid, int height)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	check_char(t_data *data, int y, int x, int *player_count)
{
	char	c;

	c = data->map->grid[y][x];
	if (c == '\t')
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MAP_FAIL_05);
	if (!ft_strchr("01NSEW ", c))
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MAP_FAIL_04);
	if (ft_strchr("NSEW", c))
	{
		(*player_count)++;
		data->player->y = (double)y + 0.5;
		data->player->x = (double)x + 0.5;
		init_player_direction(data, c);
		data->map->grid[y][x] = '0';
	}
}

void	check_map_elements(t_data *data)
{
	int	y;
	int	x;
	int	player_count;

	player_count = 0;
	y = 0;
	while (data->map->grid[y])
	{
		x = 0;
		while (data->map->grid[y][x])
		{
			check_char(data, y, x, &player_count);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MAP_FAIL_06);
}

void	validate_map(t_data *data)
{
	int		result;
	char	**temp_grid;

	check_map_elements(data);
	temp_grid = copy_matrix(data->map->grid, data->map->height);
	if (!temp_grid)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	print_mess(MSG_MAP_COPY, SUCCESS);
	result = maze_fill(temp_grid, data->player->x, data->player->y,
			*data);
	free_matrix((void **)temp_grid);
	if (result != 1)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MAP_FAIL_01);
}
