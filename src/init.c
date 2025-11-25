/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:14:22 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/24 16:43:36 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{

}

void init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_INIT_MLX);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!data->win)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_WINDOW_FAIL);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_IMG_FAIL);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	if (!data->addr)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_ADDR_FAIL);
}
