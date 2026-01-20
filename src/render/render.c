/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:13:30 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/20 14:19:23 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= mlx->screen_width || y < 0 || y >= mlx->screen_height)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	get_line_to_draw(t_ray *ray, t_mlx *mlx)
{
	ray->line_height = (int)(mlx->screen_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + mlx->screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + mlx->screen_height / 2;
	if (ray->draw_end >= mlx->screen_height)
		ray->draw_end = mlx->screen_height - 1;
}

void	set_pixel_buffer(t_mlx *mlx, t_ray *ray, t_map *map, t_player *player, int x)
{
	int		tex_id;
	int		tex_x;
	int		tex_y;
	int		y;
	int		color;
	double	wall_x; //exact value where the wall was hit, not just the integer coordinates of the wall
	double	step;
	double	tex_pos;
	t_tex	texture;

	tex_id = ray->wall_side;
	if (ray->wall_side == WEST || ray->wall_side == EAST)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	texture = mlx->tex[tex_id];
	tex_x = wall_x * (double)texture.width;
	if (ray->wall_side == EAST)
			tex_x = texture.width - tex_x - 1;
	else if (ray->wall_side == NORTH)
			tex_x = texture.width - tex_x - 1;
	get_line_to_draw(ray, mlx);
	step = (double)texture.height/(double)ray->line_height;
	tex_pos = (ray->draw_start - mlx->screen_height / 2 + ray->line_height / 2) * step;
	y = 0;
	while (y < ray->draw_start) // draw ceiling
	{
		my_mlx_pixel_put(mlx, x, y, map->ceiling_color);
		y++;
	}
	while (y < ray->draw_end) // draw walls
	{
		tex_y = (int)tex_pos & (texture.height - 1);
		tex_pos += step;
		color = mlx->tex[ray->wall_side].addr[texture.width * tex_y + tex_x];
		//TODO: maybe add darker color if y side of wall was hit (lodev)
		my_mlx_pixel_put(mlx, x, y, color);
		y++;
	}
	while (y < mlx->screen_height) // draw floor
	{
		my_mlx_pixel_put(mlx, x, y, map->floor_color);
		y++;
	}
}
