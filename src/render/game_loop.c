/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:40 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/04 17:37:18 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Calculates frame-time-dependent movement and rotation speeds.
**
** The multipliers:
** - MOVEMENT_SPEED_MULTIPLIER: Controls how fast player walks (units/second)
** - ROTATION_SPEED_MULTIPLIER: Controls how fast player rotates (radians/second)
*/
void	set_movement_and_rotation_speed(t_data *data, t_player *player)
{
	double	new_time;
	double	frame_time;

	new_time = get_current_time(data);  // Tempo attuale in secondi
	frame_time = new_time - player->time_last_frame;  // Delta time: tempo trascorso dall'ultimo frame
	player->time_last_frame = new_time;  // Aggiorna timestamp per il prossimo frame
	player->move_speed = frame_time * MOVEMENT_SPEED_MULTIPLIER;  // Velocità movimento = tempo * moltiplicatore (movimento indipendente da FPS)
	player->rot_speed = frame_time * ROTATION_SPEED_MULTIPLIER;  // Velocità rotazione = tempo * moltiplicatore (rotazione indipendente da FPS)
}

/*
** Renders a single frame to the screen.
**
** This is the core rendering pipeline called every frame:
** 1. raycasting(data):         Calculates what the player sees and draws
**                              it into the image buffer (mlx->addr)
** 2. mlx_put_image_to_window:  Displays the completed image buffer
**                              on the actual window
*/
int	render_frame(t_data *data)
{
	double	current_time;
	double	elapsed;

	current_time = get_current_time(data);  //secondi
	elapsed = current_time - data->player->last_render_time;  //tempo elapsed since last frame
	if (elapsed < FRAME_TIME_SEC)  // Se non è passato abbastanza tempo (< 16.6ms)
		return (0);  // Salta questo frame (frame limiting a ~60 FPS)
	data->player->last_render_time = current_time;
	handle_keyboard_input(data);  // Processa input tastiera e aggiorna posizione/direzione giocatore
	raycasting(data);  // Calcola e disegna tutto nel buffer immagine (raycasting + texturing)
	mlx_put_image_to_window(data->mlx->mlx,
		data->mlx->win,
		data->mlx->img, 0, 0);  // Visualizza il buffer sulla finestra (double buffering)
	return (0);  // Richiesto dalla firma di mlx_loop_hook
}

static int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		cleanup_and_exit(data, EXIT_SUCCESS, NULL);
	else if (keysym == XK_w)
		data->player->key_w = KEY_PRESSED;
	else if (keysym == XK_s)
		data->player->key_s = KEY_PRESSED;
	else if (keysym == XK_Left)
		data->player->key_left = KEY_PRESSED;
	else if (keysym == XK_Right)
		data->player->key_right = KEY_PRESSED;
	else if (keysym == XK_a)
		data->player->key_a = KEY_PRESSED;
	else if (keysym == XK_d)
		data->player->key_d = KEY_PRESSED;
	return (0);
}

static int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->player->key_w = KEY_RELEASED;
	else if (keysym == XK_s)
		data->player->key_s = KEY_RELEASED;
	else if (keysym == XK_a)
		data->player->key_a = KEY_RELEASED;
	else if (keysym == XK_d)
		data->player->key_d = KEY_RELEASED;
	else if (keysym == XK_Left)
		data->player->key_left = KEY_RELEASED;
	else if (keysym == XK_Right)
		data->player->key_right = KEY_RELEASED;
	return (0);
}

//Sets up the main game loop and event handlers.
//hook for key presses and releases
void	game_loop(t_data *data)
{
	mlx_hook(data->mlx->win,
		KeyPress,
		KeyPressMask,
		handle_keypress,
		data);
	mlx_hook(data->mlx->win,
		KeyRelease,
		KeyReleaseMask,
		handle_keyrelease,
		data);
	mlx_hook(data->mlx->win,
		DestroyNotify,
		SubstructureNotifyMask,
		handle_close_window,
		data);
	mlx_loop_hook(data->mlx->mlx, render_frame, data);  // Registra funzione chiamata continuamente (ogni iterazione del loop)
	mlx_loop(data->mlx->mlx);  // Avvia loop infinito eventi (non torna mai)
}
