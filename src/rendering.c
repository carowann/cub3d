/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:42:35 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/28 17:12:38 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Draws a vertical line on the screen representing one wall slice.
**
** This function renders three parts for column x:
** 1. Ceiling (top to start):    pixels above the wall
** 2. Wall (start to end):       the actual wall slice
** 3. Floor (end to bottom):     pixels below the wall
**
** Pixel position calculation:
** img[y * (line_length / 4) + x]
** - line_length is in bytes, we need int positions (divide by 4)
** - y * (line_length / 4) = row offset
** - + x = column offset
** - Result: exact position in the 1D image array
**
** Parameters:
** - data:  Contains image buffer and map colors
** - x:     Which screen column to draw (0 to WINDOW_WIDTH)
** - start: Y coordinate where wall begins
** - end:   Y coordinate where wall ends
** - color: Color of the wall (depends on which side was hit)
*/
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
