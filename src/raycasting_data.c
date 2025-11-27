/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:08:54 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/27 17:08:11 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Sets delta distances for the ray,
//the distance the ray has to travel to go from 1 x-side to the next x-side,
void set_delta_distances(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = DELTA_DIST_INFINITY; // A large number to avoid division by zero
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = DELTA_DIST_INFINITY; // A large number to avoid division by zero
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

//Sets step direction and initial side distances for the ray
void set_step_and_initial_side_distances(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0) //ray going to the left
	{
		ray->step_x = STEP_X_LEFT;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else //ray going to the right
	{
		ray->step_x = STEP_X_RIGHT;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0) //ray going up
	{
		ray->step_y = STEP_Y_UP;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else //ray going down
	{
		ray->step_y = STEP_Y_DOWN;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void set_perpendicular_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == NS_WALL_SIDE)
		ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}
