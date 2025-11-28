/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:42:35 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/28 15:34:12 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	int	y;
	int	*img;

	img = (int *)data->mlx->addr;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y >= start && y <= end)
			img[y * (data->mlx->line_length / 4) + x] = color;
		else if (y < start)
			img[y * (data->mlx->line_length / 4) + x] = data->map->ceiling_color;
		else
			img[y * (data->mlx->line_length / 4) + x] = data->map->floor_color;
		y++;
	}
}
