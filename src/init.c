/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:14:22 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/16 14:25:45 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data	*data)
{
	// qui mettere solo cose da inizializzare con valore, r-data inizializzato a 0 in main
	data->map = ft_calloc(1, sizeof(t_map));
	data->player = ft_calloc(1, sizeof(t_player));
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!data->map || !data->player || !data->mlx)
		cleanup_and_exit(data, EXIT_FAILURE, NULL);
	data->player->x = 0.0;
	data->player->y = 0.0;
	data->player->dir_x = 0.0;
	data->player->dir_y = 0.0;
	data->player->plane_x = 0.0;
	data->player->plane_y = 0.0;
	data->player->time_curr_frame = get_current_time(data);
	data->player->time_last_frame = 0.0;
	data->player->move_speed = 0.0;
	data->player->rot_speed = 0.0;
	data->map->width = 0;
	data->map->height = 0;
	data->mlx->tex->height = TEXTURE_HEIGHT;
	data->mlx->tex->width = TEXTURE_WIDTH;
	data->tex_path[0] = NULL;
	data->tex_path[1] = NULL;
	data->tex_path[2] = NULL;
	data->tex_path[3] = NULL;
	ft_printfd(STDOUT_FILENO, GREEN "✅ Initialised data\n" RESET);
}

/*
** Initializes all MLX components needed for graphics rendering.
** Sets up the MLX instance, creates a window, and prepares an image buffer.
** The addr pointer is crucial: it's where we write pixel colors directly.
** Instead of using slow mlx_pixel_put for each pixel, we modify addr directly
** and then display the entire image at once with mlx_put_image_to_window.
*/
void init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_INIT_MLX);
	ft_printfd(STDOUT_FILENO, GREEN "✅ Initialised mlx\n" RESET);
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!mlx->win)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_WINDOW_FAIL);
	ft_printfd(STDOUT_FILENO, GREEN "✅ Created new window\n" RESET);
	mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->img)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_IMG_FAIL);
	ft_printfd(STDOUT_FILENO, GREEN "✅ Created new image\n" RESET);
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel,
			&mlx->line_length,
			&mlx->endian);
	if (!mlx->addr)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_ADDR_FAIL);
	mlx_get_screen_size(mlx->mlx, &mlx->screen_width, &mlx->screen_height);
}
