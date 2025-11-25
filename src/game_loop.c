/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:40 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/25 12:10:24 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int	render_frame(t_data *data)
// {
// 	//update player position
// 	//raycasting(data);
// 	//mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
// 	return (0);
// }

void	game_loop(t_data *data)
{

	mlx_hook(data->mlx->win,
		DestroyNotify,
		SubstructureNotifyMask,
		handle_close_window,
		data);
	//mlx_loop_hook(data->mlx->mlx, render_frame, data);
	mlx_loop(data->mlx->mlx);
}
