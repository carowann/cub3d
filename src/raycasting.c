/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:27:10 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/28 12:04:29 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Performs the digital differential analysis (DDA) algorithm
//  to find the wall hit by the ray
static void perform_dda(t_ray *ray, t_map *map)
{
	ray->hit = 0;		  // was there a wall hit?
	while (ray->hit == 0) // perform DDA
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = NS_WALL_SIDE;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = EW_WALL_SIDE;
		}
		// Check bounds FIRST
		if (ray->map_x < 0 || ray->map_x >= map->width ||
			ray->map_y < 0 || ray->map_y >= map->height)
		{
			ray->hit = 1; // Tratta come muro
			break;
		}
		// Then check wall
		if (map->grid[ray->map_y][ray->map_x] == 1) // Nota: [y][x] non [x][y]!
			ray->hit = 1;
	}
}

static void get_line_to_draw(t_ray *ray)
{
	//Calculate height of line to draw on screen
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

int	get_color(t_ray ray)
{
	if (ray.side == 0) //NS wall
	{
		if (ray.ray_dir_x > 0)
			return (0xFF0000); // Red for East wall
		else
			return (0x00FF00); // Green for West wall
	}
	else //EW wall
	{
		if (ray.ray_dir_y > 0)
			return (0x0000FF); // Blue for South wall
		else
			return (0xFFFF00); // Yellow for North wall
	}
}

void	raycasting(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH) //for every col of the screen
	{
		ray.map_x = (int)(data->player->x); //current square of the map the player is in
		ray.map_y = (int)(data->player->y); //current square of the map the player is in
		ray.camera_x = 2 * x / (double)WINDOW_WIDTH - 1; //x-coordinate in camera space
		ray.ray_dir_x = data->player->dir_x + data->player->plane_x * ray.camera_x; //calculate ray direction x
		ray.ray_dir_y = data->player->dir_y + data->player->plane_y * ray.camera_x; //calculate ray direction y
		set_delta_distances(&ray);
		set_step_and_initial_side_distances(&ray, data->player);
		perform_dda(&ray, data->map);
		set_perpendicular_wall_distance(&ray, data->player);
		get_line_to_draw(&ray);
		draw_vertical_line(data, x, ray.draw_start, ray.draw_end, get_color(ray)); //draw a red vertical line as a placeholder
		x++;
	}
}
