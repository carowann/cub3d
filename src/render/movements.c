/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:10:24 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/05 15:03:05 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_out_of_bounds(t_map *map, int y, int x)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	return (map->grid[y][x] == WALL);
}

/*
** Moves the player forward or backward along their current direction.
**
** If ANY corner would enter a wall, movement is blocked.
** This creates a "collision box" around the player, preventing:
** - Clipping through walls
** - Getting stuck in corners
** - Walking too close to walls (sliding effect)
**
** Boundary checks:
** Also prevents player from leaving the map bounds entirely.
*/
// Controllo separato per X e Y permette "sliding" lungo i muri invece di bloccarsi completamente

void	move_forward_or_backward(t_map *map, t_player *player, int direction)
{
	double	new_x;
	double	new_y;

	new_y = player->y;  // Mantieni Y corrente temporaneamente
	new_x = player->x + player->dir_x * player->move_speed * direction; //posizione + direzione * velocità * direzione (1=avanti, -1=indietro)
	if (is_out_of_bounds(map, new_y, new_x))  // Se la nuova X entrerebbe in un muro
		new_x = player->x;  // Annulla movimento in X
	new_y = player->y + player->dir_y * player->move_speed * direction;  //posizione + direzione * velocità * direzione
	if (is_out_of_bounds(map, new_y, new_x))  // Se la nuova Y entrerebbe in un muro
		new_y = player->y;  // Annulla movimento in Y
	player->x = new_x;  // Applica nuova posizione X (valida)
	player->y = new_y;  // Applica nuova posizione Y (valida)
}

// Usa plane invece di dir perché lo strafe è perpendicolare alla direzione (A=sinistra, D=destra)
// direction: 1=destra, -1=sinistra
void	move_left_or_right(t_map *map, t_player *player, int direction)
{
	double	new_x;
	double	new_y;

	new_x = player->x + player->plane_x * player->move_speed * direction;  // Calcola nuova X usando piano camera (perpendicolare a dove guardi)
	if (is_out_of_bounds(map, (int)player->y, (int)new_x))  // Se la nuova X entrerebbe in un muro
		new_x = player->x;  // Annulla movimento in X
	new_y = player->y + player->plane_y * player->move_speed * direction;  // Calcola nuova Y usando piano camera
	if (is_out_of_bounds(map, (int)new_y, (int)new_x))  // Se la nuova Y entrerebbe in un muro
		new_y = player->y;  // Annulla movimento in Y
	player->x = new_x;  // Applica nuova posizione X
	player->y = new_y;  // Applica nuova posizione Y
}

/*
** Rotates the player's view left or right.
**
** We need to rotate TWO vectors:
** 1. Direction vector (dir_x, dir_y):  where player is looking
** 2. Camera plane (plane_x, plane_y):  defines the field of view (FOV)
**
** Both must rotate together to maintain correct perspective!
**
** 2D Rotation matrix formula:
** Given a point (x, y) and angle θ:
** new_x = x * cos(θ) - y * sin(θ)
** new_y = x * sin(θ) + y * cos(θ)
**
** Direction parameter:
** - LEFT  (A key): direction = -1 → negative angle (counterclockwise)
** - RIGHT (D key): direction = +1 → positive angle (clockwise)
**
** The rotation_angle is already scaled by frame time (rot_speed),
** ensuring smooth, consistent rotation regardless of FPS.
*/
static void	rotate_left_or_right(t_player *player, int direction)
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
		rotate_left_or_right(data->player, LEFT);
	if (data->player->key_right == KEY_PRESSED)
		rotate_left_or_right(data->player, RIGHT);
}
