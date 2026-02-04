/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:42:45 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/03 16:14:11 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_dda_variables(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		if (ray->step_x > 0)
			ray->wall_side = EAST;
		else
			ray->wall_side = WEST;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		if (ray->step_y > 0)
			ray->wall_side = SOUTH;
		else
			ray->wall_side = NORTH;
	}
}

/*
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
*/
static void	perform_dda(t_ray *ray, t_map *map)
{
	ray->hit = EMPTY;
	while (ray->hit == EMPTY)
	{
		update_dda_variables(ray);
		if (ray->map_x < 0 || ray->map_x >= map->width
			|| ray->map_y < 0 || ray->map_y >= map->height)
		{
			ray->hit = WALL;
			break ;
		}
		if (map->grid[ray->map_y][ray->map_x] == WALL)
			ray->hit = WALL;
	}
}

/*
** Main raycasting function - casts one ray per screen column.
**
** For each vertical column of the screen (x = 0 to data->mlx->screen_width):
**   1. Calculate the ray direction for that column
**   2. Use DDA to find which wall the ray hits
**   3. Calculate the distance to that wall
**   4. Calculate how tall the wall should appear on screen
**   5. Draw a vertical line representing that wall slice
*/
void	raycasting(t_data *data)
{
	int		x;
	t_ray	r; //tutti i dati di un singolo raggio

	x = 0;
	while (x < data->mlx->screen_width)
	{
		r.map_x = (int)(data->player->x); //coord della cella della griglia in cui si trova p (partenza raggio)
		r.map_y = (int)(data->player->y);
		r.camera_x = 2 * x / (double)data->mlx->screen_width - 1; //mappa x(colonna) nell'intervallo -1, 1
		r.ray_dir_x = data->player->dir_x + data->player->plane_x * r.camera_x; //dir raggio per questa col
		r.ray_dir_y = data->player->dir_y + data->player->plane_y * r.camera_x;
		set_delta_distances(&r); //quanto deve viaggiare un ray attaverso una cella (x, y)
		set_step_and_initial_side_distances(&r, data->player); //dir di step e quanto manca alla prima linea della griglia
		perform_dda(&r, data->map); //marcia nella griglia fino a trovare un muro
		set_perpendicular_wall_distance(&r, data->player); //distanza corretta al muro senza fisheye
		set_pixel_buffer(data, &r, x); //date le info raccolte, disegna colonna
		x++;
	}
}
