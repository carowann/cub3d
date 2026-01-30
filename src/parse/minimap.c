/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:42:47 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/30 18:01:15 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

static	void	my_other_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= mlx->screen_width || y < 0 || y >= mlx->screen_height)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_minimap_tile(t_data *data, int x, int y, int color)
{
	int i;
	int j;
	int start_x = x * MM_TILE_SIZE + 20;
	int start_y = y * MM_TILE_SIZE + 20;

	i = 0;
	while (i < MM_TILE_SIZE)
	{
		j = 0;
		while (j < MM_TILE_SIZE)
		{
			// bordo griglia verde: 0x00AC12
			if (i == 0 || j == 0)
				my_other_pixel_put(data->mlx, start_x + j, start_y + i,0x000000);
			else
				my_other_pixel_put(data->mlx, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data) //meh
{
	int y;
	int x;
	int i;
	int j;

	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			if (data->map->grid[y][x] == '1')
				draw_minimap_tile(data, x, y, MM_COLOR_WALL);
			else if (data->map->grid[y][x] == '0' || ft_strchr("NSEW", data->map->grid[y][x]))
				draw_minimap_tile(data, x, y, MM_COLOR_FLOOR);
		}
	}
	int px = data->player->x * MM_TILE_SIZE + 20;
	int py = data->player->y * MM_TILE_SIZE + 20;
	i = -2;
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			my_other_pixel_put(data->mlx, px + j, py + i, MM_COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

int	render_mm_frame(t_data *data)
{
	raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
	return (0);
}
