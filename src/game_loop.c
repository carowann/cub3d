/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:40 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/28 17:18:36 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Calculates frame-time-dependent movement and rotation speeds.
**
** Why frame time matters:
** Different computers run at different speeds (30 FPS, 60 FPS, 144 FPS, etc.)
** Without frame time compensation:
** - Fast computer: player moves super fast (bad!)
** - Slow computer: player moves in slow motion (bad!)
**
** Solution: Delta time (frame time)
** Speed = base_speed * time_elapsed_since_last_frame
** This ensures consistent movement speed regardless of FPS.
**
** Special case:
** On the very first frame (time_last_frame = 0), we don't have a previous
** frame to compare with, so we use a default frame time (FRAME_TIME_SEC).
**
** The multipliers:
** - MOVEMENT_SPEED_MULTIPLIER: Controls how fast player walks (units/second)
** - ROTATION_SPEED_MULTIPLIER: Controls how fast player rotates (radians/second)
*/
static void	set_movement_and_rotation_speed(t_data *data, t_player *player)
{
	double	new_time;
	double	frame_time;

	new_time = get_current_time(data);
	if (player->time_last_frame == 0.0)
		frame_time = FRAME_TIME_SEC;
	else
		frame_time = new_time - player->time_last_frame;
	player->time_last_frame = new_time;
	// Calculate speeds based on elapsed time
	// More time elapsed = bigger movement this frame
	player->move_speed = frame_time * MOVEMENT_SPEED_MULTIPLIER;
	player->rot_speed = frame_time * ROTATION_SPEED_MULTIPLIER;
}

/*
** Renders a single frame to the screen.
**
** This is the core rendering pipeline called every frame:
** 1. raycasting(data):         Calculates what the player sees and draws
**                              it into the image buffer (mlx->addr)
** 2. mlx_put_image_to_window:  Displays the completed image buffer
**                              on the actual window
**
** Why two steps?
** - Drawing directly to the window pixel-by-pixel is SLOW
** - Instead, we draw everything to an off-screen buffer (mlx->img)
** - Then display the entire image at once (much faster, no flickering)
**
** This technique is called "double buffering" and ensures smooth graphics.
**
** Return: 0 (required by mlx_loop_hook)
*/
int	render_frame(t_data *data)
{
	raycasting(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	set_movement_and_rotation_speed(data, data->player);
	if (keysym == XK_Escape)
		cleanup_and_exit(data, EXIT_SUCCESS, NULL);
	else if (keysym == XK_w || keysym == XK_Up)
		move_forward_or_backward(data->map, data->player, UP);
	else if (keysym == XK_s || keysym == XK_Down)
		move_forward_or_backward(data->map, data->player, DOWN);
	else if (keysym == XK_a || keysym == XK_Left)
		rotate_left_or_right(data->player, LEFT);
	else if (keysym == XK_d || keysym == XK_Right)
		rotate_left_or_right(data->player, RIGHT);
	render_frame(data);
	return (0);
}


//Sets up the main game loop and event handlers.
void	game_loop(t_data *data)
{
	mlx_hook(data->mlx->win, //Window to monitor for events
		KeyPress, //Event type: Key press
		KeyPressMask, //Event mask for key presses
		handle_keypress, //Function to call on key press
		data); //Parameter to pass to the function
	mlx_hook(data->mlx->win,
		DestroyNotify,
		SubstructureNotifyMask,
		handle_close_window,
		data);
	mlx_loop_hook(data->mlx->mlx, render_frame, data); // Register continuous rendering function (called every frame)
	mlx_loop(data->mlx->mlx); // Start the infinite event loop (program runs here until exit)
}

