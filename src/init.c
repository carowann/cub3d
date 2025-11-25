/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:14:22 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/25 13:53:08 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data	*data)
{
	data->map = malloc(sizeof(t_map));
	data->player = malloc(sizeof(t_player));
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->map || !data->player || !data->mlx)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_NONE);
	// Initialize player position and direction
	data->player->x = 5.0;
	data->player->y = 5.0;
	data->player->dir_x = -1.0;
	data->player->dir_y = 0.0;
	data->player->plane_x = 0.0;
	data->player->plane_y = 0.66;
	data->mlx->mlx = NULL;
	data->mlx->win = NULL;
	data->mlx->img = NULL;
	data->mlx->addr = NULL;
	data->mlx->bits_per_pixel = 0;
	data->mlx->line_length = 0;
	data->mlx->endian = 0;
	data->map->width = 0;
	data->map->height = 0;
}

void init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_INIT_MLX);
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!mlx->win)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_WINDOW_FAIL);
	mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->img)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_IMG_FAIL);
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel,
			&mlx->line_length,
			&mlx->endian);
	if (!mlx->addr)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_ADDR_FAIL);
}
