/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:14:22 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/29 14:27:26 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data	*data)
{
	data->map = ft_calloc(1, sizeof(t_map));
	data->player = ft_calloc(1, sizeof(t_player));
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!data->map || !data->player || !data->mlx)
		cleanup_and_exit(data, EXIT_FAILURE, NULL);
	data->player->time_curr_frame = get_current_time(data);
	print_mess(MSG_DATA_OK, SUCCESS);
}

/*
** Initializes all MLX components needed for graphics rendering.
** Sets up the MLX instance, creates a window, and prepares an image buffer.
** The addr pointer is crucial: it's where we write pixel colors directly.
** Instead of using slow mlx_pixel_put for each pixel, we modify addr directly
** and then display the entire image at once with mlx_put_image_to_window.
*/
void	init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_INIT_MLX);
	print_mess(MSG_MLX_INIT, SUCCESS);
	mlx_get_screen_size(mlx->mlx, &mlx->screen_width, &mlx->screen_height);
	ft_printfd(STDOUT_FILENO, GREEN "✅ Screen size = %d x %d\n" RESET,
		mlx->screen_width, mlx->screen_height);
	mlx->aspect_ratio = (double)mlx->screen_width / (double)mlx->screen_height;
	mlx->win = mlx_new_window(mlx->mlx, mlx->screen_width, mlx->screen_height,
			"Cub3D");
	if (!mlx->win)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_WINDOW_FAIL);
	print_mess(MSG_WIN_OK, SUCCESS);
	mlx->img = mlx_new_image(mlx->mlx, mlx->screen_width, mlx->screen_height);
	if (!mlx->img)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_IMG_FAIL);
	print_mess(MSG_IMG_OK, SUCCESS);
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel,
			&mlx->line_length,
			&mlx->endian);
	if (!mlx->addr)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_ADDR_FAIL);
}
