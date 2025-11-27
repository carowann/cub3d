/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:40 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/27 18:16:05 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_movement_and_rotation_speed(t_data *data, t_player *player)
{
	double	frame_time;

	player->time_last_frame = player->time_curr_frame;
	player->time_curr_frame = get_current_time(data);
	frame_time = player->time_curr_frame - player->time_last_frame;
	player->move_speed = frame_time * MOVEMENT_SPEED_MULTIPLIER;
	player->rot_speed = frame_time * ROTATION_SPEED_MULTIPLIER;
}

int	render_frame(t_data *data)
{
	set_movement_and_rotation_speed(data, data->player);
	raycasting(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cleanup_and_exit(data, EXIT_SUCCESS, NULL);
	else if (keysym == XK_w || keysym == XK_Up)
		move_forward_or_backward(data->map, data->player, UP);
	else if (keysym == XK_s || keysym == XK_Down)
		move_forward_or_backward(data->map, data->player, DOWN);
	else if (keysym == XK_a || keysym == XK_Left)
		rotate_left_or_right(data->map, data->player, LEFT);
	else if (keysym == XK_d || keysym == XK_Right)
		rotate_left_or_right(data->map, data->player, RIGHT);
	return (0);
}

void	game_loop(t_data *data)
{
	mlx_hook(data->mlx->win,
		KeyPress,
		KeyPressMask,
		handle_keypress,
		data);
	mlx_hook(data->mlx->win,
		DestroyNotify,
		SubstructureNotifyMask,
		handle_close_window,
		data);
	mlx_loop_hook(data->mlx->mlx, render_frame, data);
	mlx_loop(data->mlx->mlx);
}

