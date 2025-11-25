/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:27:45 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/25 09:49:14 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	print_error_message(int msg_code)
{
	if (msg_code == MSG_N_ARGS)
		ft_printfd(STDERR_FILENO, "Error\nInvalid number of arguments.\n");
	else if (msg_code == MSG_CUB_EXT)
		ft_printfd(STDERR_FILENO, "Error\nInvalid file extension. Expected .cub\n");
	else if (msg_code == MSG_INIT_MLX)
		ft_printfd(STDERR_FILENO, "Error\nFailed to initialize MLX.\n");
	else if (msg_code == MSG_WINDOW_FAIL)
		ft_printfd(STDERR_FILENO, "Error\nFailed to create window.\n");
	else if (msg_code == MSG_IMG_FAIL)
		ft_printfd(STDERR_FILENO, "Error\nFailed to create image.\n");
	else if (msg_code == MSG_ADDR_FAIL)
		ft_printfd(STDERR_FILENO, "Error\nFailed to get image address.\n");
	}

int	cleanup_and_exit(t_data *data, int exit_code, int msg_code)
{
	if (msg_code)
		print_error_message(msg_code);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(exit_code);
}

int	handle_close_window(t_data *data)
{
	cleanup_and_exit(data, EXIT_SUCCESS, MSG_NONE);
	return (0);
}
