/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:27:10 by cwannhed          #+#    #+#             */
/*   Updated: 2025/12/12 15:21:55 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	update_dda_variables(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		if (ray->step_x > 0)
			ray->wall_side = WEST;
		else
			ray->wall_side = EAST;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		if (ray->step_y > 0)
			ray->wall_side = NORTH;
		else
			ray->wall_side = SOUTH;
	}
}

/*
** Performs the DDA (Digital Differential Analysis) algorithm.
**
** DDA steps through the map grid square by square until hitting a wall.
** At each step, it chooses whether to cross a vertical or horizontal grid line
** based on which is closer.
**
** How it works:
** 1. Compare side_dist_x vs side_dist_y (which grid line is closer?)
** 2. Jump to the closer grid line
** 3. Update position in the map (map_x or map_y)
** 4. Add delta_dist for the next jump
** 5. Check if we hit a wall
** 6. Repeat until wall found
**
** Side tracking (NS_WALL_SIDE vs EW_WALL_SIDE):
** - NS_WALL_SIDE: Hit a North/South wall (vertical line crossed)
** - EW_WALL_SIDE: Hit an East/West wall (horizontal line crossed)
** - Used later for coloring walls differently based on orientation
**
** Safety check:
** If ray goes outside map bounds, we treat it as a wall hit to prevent crashes.
*/
static void	perform_dda(t_ray *ray, t_map *map)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		update_dda_variables(ray);
		if (ray->map_x < 0 || ray->map_x >= map->width
			|| ray->map_y < 0 || ray->map_y >= map->height)
		{
			ray->hit = 1;
			break ;
		}
		if (map->grid[ray->map_y][ray->map_x] == 1)
			ray->hit = 1;
	}
}

/*
** Main raycasting function - casts one ray per screen column.
**
** Raycasting algorithm overview:
** For each vertical column of the screen (x = 0 to WINDOW_WIDTH):
**   1. Calculate the ray direction for that column
**   2. Use DDA to find which wall the ray hits
**   3. Calculate the distance to that wall
**   4. Calculate how tall the wall should appear on screen
**   5. Draw a vertical line representing that wall slice
**
** This creates a 3D perspective from a 2D map by:
** - Casting rays from the player's position
** - Drawing walls taller when they're closer, shorter when far
** - Using different colors based on which wall side was hit
**
** Key concept: Each screen column = one ray = one vertical line
*/
void	raycasting(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH) // Cast one ray per screen column
	{
		ray.map_x = (int)(data->player->x); // Initialize ray starting position (player's current map square)
		ray.map_y = (int)(data->player->y); // Initialize ray starting position (player's current map square)
		// Convert screen x-coordinate to camera space [-1, 1]
		// Left edge = -1, center = 0, right edge = 1
		ray.camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		// Calculate ray direction by combining:
		// - Player's direction vector (where they're facing)
		// - Camera plane vector (FOV/field of view)
		ray.ray_dir_x = data->player->dir_x + data->player->plane_x * ray.camera_x;
		ray.ray_dir_y = data->player->dir_y + data->player->plane_y * ray.camera_x;
		set_delta_distances(&ray);
		set_step_and_initial_side_distances(&ray, data->player);
		// Perform DDA: step through the map until hitting a wall
		perform_dda(&ray, data->map);
		// Calculate perpendicular distance to avoid fisheye effect
		set_perpendicular_wall_distance(&ray, data->player);
		set_pixel_buffer(data->mlx, &ray, data->map, data->player, x);
		x++;
	}
}
