/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:40 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/24 17:03:12 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	game_engine_loop(t_data *data)
{
	// Placeholder for the main game loop logic
	// This would typically include rendering, input handling, etc.
	mlx_hook(data->win,
		DestroyNotify,
		SubstructureNotifyMask,
		cleanup_and_exit,
		data);
	mlx_loop(data->mlx);
}
