/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:10:24 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/09 10:32:47 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	is_out_of_bounds(t_map *map, int y, int x)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	return (map->grid[y][x] == WALL);
}

void	move_forward_or_backward(t_map *map, t_player *player, int direction)
{
	double	new_x;
	double	new_y;

	new_y = player->y;
	new_x = player->x + player->dir_x * player->move_speed * direction;
	if (is_out_of_bounds(map, new_y, new_x))
		new_x = player->x;
	new_y = player->y + player->dir_y * player->move_speed * direction;
	if (is_out_of_bounds(map, new_y, new_x))
		new_y = player->y;
	player->x = new_x;
	player->y = new_y;
}

void	move_left_or_right(t_map *map, t_player *player, int direction)
{
	double	new_x;
	double	new_y;

	new_x = player->x + player->plane_x * player->move_speed * direction;
	if (is_out_of_bounds(map, (int)player->y, (int)new_x))
		new_x = player->x;
	new_y = player->y + player->plane_y * player->move_speed * direction;
	if (is_out_of_bounds(map, (int)new_y, (int)new_x))
		new_y = player->y;
	player->x = new_x;
	player->y = new_y;
}

void	rotate_player(t_data *data, double angle_speed)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = data->player;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(angle_speed) - p->dir_y * sin(angle_speed);
	p->dir_y = old_dir_x * sin(angle_speed) + p->dir_y * cos(angle_speed);
	p->plane_x = p->plane_x * cos(angle_speed) - p->plane_y * sin(angle_speed);
	p->plane_y = old_plane_x * sin(angle_speed) + p->plane_y * cos(angle_speed);
}

void	handle_keyboard_input(t_data *data)
{
	set_movement_and_rotation_speed(data, data->player);
	if (data->player->key_w == KEY_PRESSED)
		move_forward_or_backward(data->map, data->player, UP);
	if (data->player->key_s == KEY_PRESSED)
		move_forward_or_backward(data->map, data->player, DOWN);
	if (data->player->key_a == KEY_PRESSED)
		move_left_or_right(data->map, data->player, LEFT);
	if (data->player->key_d == KEY_PRESSED)
		move_left_or_right(data->map, data->player, RIGHT);
	if (data->player->key_left == KEY_PRESSED)
		rotate_player(data, -1.0);
	if (data->player->key_right == KEY_PRESSED)
		rotate_player(data, 1.0);
}
