/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:35:09 by giomastr          #+#    #+#             */
/*   Updated: 2026/02/03 11:02:28 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	mouse_handler(int x, int y, t_data *data)
{
    static int last_x = -1; // Per gestire il primo movimento
    int diff_x;
    (void)y;

    if (last_x == -1)  // Inizializziamo last_x al centro se è la prima volta
        last_x = data->mlx->screen_width / 2;
    if (x == data->mlx->screen_width / 2 && y == data->mlx->screen_height / 2)
        return (0); //controllo se e' gia' al centro
    // 1. Calcola lo spostamento
    diff_x = x - last_x;
    // 2. Se c'è movimento, ruota
    if (diff_x != 0)
    {
        // Dividiamo diff_x per regolare la sensibilità
        // Più alto è il divisore, più lento e preciso è il mouse
        rotate_left_or_right(data->player, (double)diff_x / 5.0);
    }

    // 3. Opzionale: Mantieni il mouse bloccato al centro (FPS Style)
    // Se lo fai, last_x sarà sempre data->mlx->screen_width / 2
    mlx_mouse_move(data->mlx->mlx, data->mlx->win, data->mlx->screen_width / 2, data->mlx->screen_height / 2);
    last_x = data->mlx->screen_width / 2;

    return (0);
}