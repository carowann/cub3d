/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:10:24 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/28 15:19:19 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void move_forward_or_backward(t_map *map, t_player *player, int direction)
{
	double new_x;
	double new_y;
	double margin;

	margin = WALL_MARGIN; // Safety margin from walls
	new_x = player->x + player->dir_x * player->move_speed * direction;
	new_y = player->y + player->dir_y * player->move_speed * direction;
	if (new_x < margin || new_x >= map->width - margin ||
		new_y < margin || new_y >= map->height - margin)
		return;
	if (map->grid[(int)(new_y - margin)][(int)(new_x - margin)] == WALL ||
		map->grid[(int)(new_y - margin)][(int)(new_x + margin)] == WALL ||
		map->grid[(int)(new_y + margin)][(int)(new_x - margin)] == WALL ||
		map->grid[(int)(new_y + margin)][(int)(new_x + margin)] == WALL)
		return;
	player->x = new_x;
	player->y = new_y;
}

void	rotate_left_or_right(t_player *player, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation_angle;

	rotation_angle = player->rot_speed * direction;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotation_angle)
		- player->dir_y * sin(rotation_angle);
	player->dir_y = old_dir_x * sin(rotation_angle)
		+ player->dir_y * cos(rotation_angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rotation_angle)
		- player->plane_y * sin(rotation_angle);
	player->plane_y = old_plane_x * sin(rotation_angle)
		+ player->plane_y * cos(rotation_angle);
}
