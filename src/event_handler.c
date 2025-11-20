/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:01:00 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/20 16:23:25 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cubed.h"

void	init_events(t_cubed *cubd)
{
	mlx_hook(cubd->mlx_win,
		KeyPress, KeyPressMask, key_press, cubd); // all of the keys
	// mlx_hook(cubd->mlx_win,
	// 	ButtonPress, ButtonPressMask, mouse_press, cubd); // mouse
	mlx_hook(cubd->mlx_win,
		DestroyNotify, StructureNotifyMask, free_all, cubd); // x on window
}

int	key_press(int keysym, t_cubed *cubd)
{
	printf("%d\n", keysym);
	// double step = 0.1 * cubd->zoom;
	if (keysym == XK_Escape)
		free_all(cubd, 1);
	else if (keysym == XK_Left)//65361
		//move camera to the left
	else if (keysym == XK_Right)//65363
		//move camera to the right
	else if (keysym == XK_Up)//65362
		cubd->shifty += step;
	else if (keysym == XK_Down)//65364
		cubd->shifty -= step;
	else if (keysym == (XK_plus | plus))
		cubd->iter_def += 10;
	else if (keysym == (XK_minus | minus))
		cubd->iter_def -= 10;
	else if(keysym == C)
		change_colour(cubd);
	rendering(cubd);// need to recall it here to update image
	return (0);
}

int	mouse_press(int button, int x, int y, t_cubed *cubd)
{
	(void)x;
	(void)y;
	if (button == Button4 && cubd->zoom > QB_IN)
	{
		cubd->zoom *= 0.9;
		cubd->shiftx += ((plane_to_map(x, -2.0, +2.0, WIDTH) * cubd->zoom) / 10);
		cubd->shifty += ((plane_to_map(y, +2.0, -2.0, HEIGHT) * cubd->zoom) / 10);
	}
	else if (button == Button5 && cubd->zoom < QB_OUT)
	{
		cubd->zoom /= 0.9;
		cubd->shiftx -= ((plane_to_map(x, -2.0, +2.0, WIDTH) * cubd->zoom) / 10);
		cubd->shifty -= ((plane_to_map(y, +2.0, -2.0, HEIGHT) * cubd->zoom) / 10);
	}
	rendering(cubd);
	return (0);
}