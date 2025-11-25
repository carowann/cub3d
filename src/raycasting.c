/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:27:10 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/25 17:44:48 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void set_delta_distances(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30; // A large number to avoid division by zero
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30; // A large number to avoid division by zero
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void set_step_and_initial_side_distances(t_ray *ray, t_player *player, int map_x, int map_y)
{
	if (ray->ray_dir_x < 0) //ray going to the left
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - map_x) * ray->delta_dist_x;
	}
	else //ray going to the right
	{
		ray->step_x = 1;
		ray->side_dist_x = (map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0) //ray going up
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - map_y) * ray->delta_dist_y;
	}
	else //ray going down
	{
		ray->step_y = 1;
		ray->side_dist_y = (map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	raycasting(t_data *data)
{
	int		x;
	int		map_x;
	int		map_y;
	t_ray	ray;

	x = 0;
	map_x = (int)(data->player->x); //current square of the map the player is in
	map_y = (int)(data->player->y); //current square of the map the player is in
	while (x < WINDOW_WIDTH) //for every col of the screen
	{
		ray.camera_x = 2 * x / (double)WINDOW_WIDTH - 1; //x-coordinate in camera space
		ray.ray_dir_x = data->player->dir_x + data->player->plane_x * ray.camera_x; //calculate ray direction x
		ray.ray_dir_y = data->player->dir_y + data->player->plane_y * ray.camera_x; //calculate ray direction y
		set_delta_distances(&ray);
		set_step_and_initial_side_distances(&ray, data->player, map_x, map_y);
		draw_vertical_line(data, x, 100, 400, 0xFF0000); //draw a red vertical line as a placeholder
		x++;
	}
}
