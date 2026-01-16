/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:56:30 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/16 14:26:28 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_player_direction(t_data *data, char c)
{
	// Reset iniziale
	data->player->dir_x = 0;
	data->player->dir_y = 0;
	data->player->plane_x = 0;
	data->player->plane_y = 0;

	if (c == 'N') {
		data->player->dir_y = -1.0;  // Guarda su (Y negativa)
		data->player->plane_x = 0.66; // Piano orizzontale
	}
	else if (c == 'S') {
		data->player->dir_y = 1.0;   // Guarda giù (Y positiva)
		data->player->plane_x = -0.66;
	}
	else if (c == 'E') {
		data->player->dir_x = 1.0;   // Guarda a destra (X positiva)
		data->player->plane_y = 0.66; // Piano verticale
	}
	else if (c == 'W') {
		data->player->dir_x = -1.0;  // Guarda a sinistra (X negativa)
		data->player->plane_y = -0.66;
	}
}

void	check_map_elements(t_data *data)
{
	int		y;
	int		x;
	int		player_count;
	char	c;

	player_count = 0;
	y = 0;
	while (data->map->grid[y])
	{
		x = 0;
		while (data->map->grid[y][x])
		{
			c = data->map->grid[y][x];
			if (!ft_strchr("01NSEW ", c))
				cleanup_and_exit(data, EXIT_FAILURE, MSG_MAP_FAIL_04);
			if (ft_strchr("NSEW", c))
			{
				player_count++;
				data->player->y = (double)y + 0.5; // +0.5 per metterlo al centro della cella
				data->player->x = (double)x + 0.5;
				init_player_direction(data, c); // <--- Chiamata qui
				data->map->grid[y][x] = '0';
				ft_printfd(STDOUT_FILENO, GREEN "✅ Saved player coordinates y = %d, x = %d with orientation %c\n" RESET, y, x, c);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MAP_FAIL_05);
}

void validate_map(t_data *data)
{
	int		result;
	char	**temp_grid;

	check_map_elements(data);									 // prima scorri matrice e controlla elementi
	temp_grid = copy_matrix(data->map->grid, data->map->height); // duplica per flood
	if (!temp_grid)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	// printf("map copied succesfully!\n"); // remove later
	// 3. Esecuzione Flood Fill sulla copia
	// Partiamo dalla posizione del player salvata in check_map_elements
	result = maze_fill(temp_grid, data->player->x, data->player->y,
						data->map->width, data->map->height);
	free_matrix((void **)temp_grid);
	if (result != 1)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MAP_FAIL_03);
}
