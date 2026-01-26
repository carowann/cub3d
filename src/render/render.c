/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:13:30 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/26 14:59:09 by cwannhed         ###   ########.fr       */
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
	double	corrected_height;

	corrected_height = mlx->screen_height * sqrt(mlx->aspect_ratio);
	ray->line_height = (int)(corrected_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + mlx->screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + mlx->screen_height / 2;
	if (ray->draw_end >= mlx->screen_height)
		ray->draw_end = mlx->screen_height - 1;
}

static void	set_tex_x_coord(t_ray *ray, t_player *player, t_tex *tex)
{
	double	wall_x;

	if (ray->wall_side == WEST || ray->wall_side == EAST)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex->x = wall_x * (double)tex->width;
	if (ray->wall_side == EAST)
		tex->x = tex->width - tex->x - 1;
	else if (ray->wall_side == NORTH)
		tex->x = tex->width - tex->x - 1;
}

static void	draw_column(t_ray ray, t_data d, int x, t_tex tex)
{
	int		y;
	int		color;

	y = 0;
	while (y < ray.draw_start)
	{
		my_mlx_pixel_put(d.mlx, x, y, d.map->ceiling_color);
		y++;
	}
	while (y < ray.draw_end)
	{
		tex.y = (int)tex.pos & (tex.height - 1);
		tex.pos += tex.step;
		color = d.mlx->tex[ray.wall_side].addr[tex.width * tex.y + tex.x];
		//TODO: maybe add darker color if y side of wall was hit (lodev)
		my_mlx_pixel_put(d.mlx, x, y, color);
		y++;
	}
	while (y < d.mlx->screen_height)
	{
		my_mlx_pixel_put(d.mlx, x, y, d.map->floor_color);
		y++;
	}
}

void	set_pixel_buffer(t_data *d, t_ray *ray, int x)
{
	int		tex_id;
	t_tex	tex;

	tex_id = ray->wall_side;
	tex = d->mlx->tex[tex_id];
	set_tex_x_coord(ray, d->player, &tex);
	get_line_to_draw(ray, d->mlx);
	tex.step = (double)tex.height / (double)ray->line_height;
	tex.pos = (ray->draw_start - d->mlx->screen_height / 2
			+ ray->line_height / 2) * tex.step;
	draw_column(*ray, *d, x, tex);
}
