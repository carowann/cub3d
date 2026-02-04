/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:35:09 by giomastr          #+#    #+#             */
/*   Updated: 2026/02/03 17:00:46 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	mouse_handler(int x, int y, t_data *data)
{
	int	diff_x;

	diff_x = x - data->mlx->screen_width / 2;
	if (x == data->mlx->screen_width / 2 && y == data->mlx->screen_height / 2)
		return (0);
	if (diff_x == 0)
		return (0);
	rotate_player(data, diff_x * MOUSE_DPI);
	mlx_mouse_move(data->mlx->mlx, data->mlx->win,
		data->mlx->screen_width / 2, data->mlx->screen_height / 2);
	return (0);
}
