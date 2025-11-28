/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:10:24 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/28 13:18:11 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void	move_forward_or_backward(t_map *map, t_player *player, int direction)
{
	double	x_increment;
	double	y_increment;
	double	new_x;
	double	new_y;

	x_increment = (player->dir_x * player->move_speed * direction);
	y_increment = (player->dir_y * player->move_speed * direction);
	new_x = (player->x + x_increment);
	new_y = (player->y + y_increment);
	if (map->grid[(int)(player->y)][(int)new_x] != WALL)
		player->x += x_increment;
	if (map->grid[(int)new_y][(int)(player->x)] != WALL)
		player->y += y_increment;
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
