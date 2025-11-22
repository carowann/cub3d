/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:57:19 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/22 15:06:17 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init_data(t_cubed *cubd)
// {
	// 	cubd->escape_val = 4; // 2'2 - the hypotenuse
	// 	cubd->iter_def = 50;
	// 	cubd->shiftx = 0.0;
	// 	cubd->shifty = 0.0;
	// 	cubd->zoom = 1.0;
	// 	cubd->colour = ELECTRIC_BLUE;
	// 	cubd->index = 0;
// }

// void	init_error(t_cubed *cubd)
// {
	// 	perror("init and malloc issues");
	// 	free_all(cubd, EXIT_FAILURE);
// }

// int	free_all(t_cubed *cubd, int status)
// {
	// 	(void)cubd;
	// 	if (cubd->start_mlx != NULL)
	// 	{
	// 		if (cubd->img.img_ptr != NULL)
	// 			mlx_destroy_image(cubd->start_mlx, cubd->img.img_ptr);
	// 		if (cubd->mlx_win != NULL)
	// 			mlx_destroy_window(cubd->start_mlx, cubd->mlx_win);
	// 		mlx_destroy_display(cubd->start_mlx);
	// 		free(cubd->start_mlx);
	// 	}
	// 	exit(status);
	// 	return (1);
// }

// void	mlx_magic(t_cubed *cubd)
// {
	// 	cubd->start_mlx = mlx_init();
	// 	if (cubd->start_mlx == NULL)//initialization fails
	// 		init_error(cubd);
	// 	cubd->mlx_win = mlx_new_window(cubd->start_mlx, WIDTH, HEIGHT, "CUB3D");
	// 	if (cubd->mlx_win == NULL)//new window fails
	// 		init_error(cubd);
	// 	cubd->img.img_ptr = mlx_new_image(cubd->start_mlx, WIDTH, HEIGHT);
	// 	if (cubd->img.img_ptr == NULL)//new image fails
	// 		init_error(cubd);
	// 	cubd->img.pix_ptr = mlx_get_data_addr(cubd->img.img_ptr, &cubd->img.bitxpix,
	// 			&cubd->img.line_len, &cubd->img.endian);
	// 	if (cubd->img.pix_ptr == NULL)
	// 		init_error(cubd);
	// 	init_data(cubd);
	// 	init_events(cubd);
// }