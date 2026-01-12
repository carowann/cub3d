/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:13:30 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/12 16:50:53 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	get_line_to_draw(t_ray *ray)
{
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

void set_pixel_buffer(t_mlx *mlx, t_ray *ray, t_map *map, t_player *player, int x)
{
	int		tex_id;
	int		tex_x;
	int		tex_y;
	int		y;
	int		color;
	double	wall_x; //exact value where the wall was hit, not just the integer coordinates of the wall
	double	step;
	double	tex_pos;

	tex_id = ray->wall_side;
	if (ray->wall_side == WEST || ray->wall_side == EAST)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * (double)TEXTURE_WIDTH;
	if (ray->wall_side == WEST || ray->wall_side == EAST)
	{
		if (ray->ray_dir_x > 0)
			tex_x = TEXTURE_WIDTH - tex_x - 1;
	}
	else // NORTH or SOUTH
	{
		if (ray->ray_dir_y < 0)
			tex_x = TEXTURE_WIDTH - tex_x - 1;
	}
	get_line_to_draw(ray);
	step = (double)TEXTURE_HEIGHT/(double)ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	y = 0;
	while (y < ray->draw_start) // draw ceiling
	{
		my_mlx_pixel_put(mlx, x, y, map->ceiling_color);
		y++;
	}
	while (y < ray->draw_end) // draw walls
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		color = mlx->tex[ray->wall_side].addr[TEXTURE_WIDTH * tex_y + tex_x];
		//TODO: maybe add darker color if y side of wall was hit (lodev)
		my_mlx_pixel_put(mlx, x, y, color);
		y++;
	}
	while (y < WINDOW_HEIGHT) // draw floor
	{
		my_mlx_pixel_put(mlx, x, y, map->floor_color);
		y++;
	}
}
