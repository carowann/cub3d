/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:08:54 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/04 12:31:39 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
** Calculates delta distances for the DDA algorithm.
**
** Delta distance = how far the ray must travel to cross one map grid square
** in the x or y direction.
**
** Why we need this:
** The DDA algorithm steps through the map grid square by square.
** Delta distances tell us "how much does the ray travel to go from one
** grid line to the next?"
**
** Mathematical explanation:
** - If ray travels horizontally (ray_dir_x = 1, ray_dir_y = 0):
**   delta_dist_x = 1 (travels 1 unit to cross one square)
**   delta_dist_y = infinity (never crosses horizontal lines)
**
** - If ray travels diagonally (ray_dir_x = 0.6, ray_dir_y = 0.8):
**   delta_dist_x = 1/0.6 = 1.67 (travels 1.67 units to cross one vertical line)
**   delta_dist_y = 1/0.8 = 1.25 (travels 1.25 units to cross one horiz line)
**
** Special case:
** If ray_dir is 0 (ray perfectly horizontal/vertical), we use INFINITY
** to avoid division by zero. This means "never crosses that axis".
*/
void	set_delta_distances(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/*
** Sets up the DDA algorithm by determining:
** 1. Step direction: which way to move through the map grid (+1 or -1)
** 2. Initial side distances: how far until the ray hits the FIRST grid line
**
** Step direction (step_x, step_y):
** - Determines if we move forward (+1) or backward (-1) through map squares
** - Based on ray direction (left/right for x, up/down for y)
**
** Initial side distance:
** - Distance from player position to the FIRST vertical/horizontal grid line
** - After this, we add delta_dist to cross subsequent grid lines
** - Calculated differently based on ray direction to handle fractional positions
**
** - step_x = +1 (moving right)
** - side_dist_x = (3.0 - 2.3) * delta_dist_x  ← Distance to first vertical line
** - After crossing: add delta_dist_x to reach next line
**
** This setup allows DDA to efficiently step through the map grid.
*/
void	set_step_and_initial_side_distances(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

/*
** Calculates the perpendicular distance from player to the wall.
**
** Why perpendicular distance?
** - The actual ray length creates a "fisheye effect" (curved walls)
** - Perpendicular distance = shortest distance to wall plane
** - This gives us straight walls (correct perspective)
**
** The formula:
** - Takes the difference between wall position and player position
** - Adds (1 - step) / 2 to account for which side of the square we hit
**   * If step = +1 (going right/down): adds 0, we hit left/top side
**   * If step = -1 (going left/up): adds 1, we hit right/bottom side
** - Divides by ray direction to get perpendicular component
**
** This distance is used to calculate wall height on screen:
** taller walls = closer, shorter walls = farther
*/
void	set_perpendicular_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->wall_side == WEST || ray->wall_side == EAST)
		ray->perp_wall_dist = (ray->map_x - player->x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}
