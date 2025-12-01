/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:27:45 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/26 17:09:55 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_err_mess(int msg_code)
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
	else if (msg_code == MSG_IS_DIR)
		ft_printfd(STDERR_FILENO, "Error\nIt's a directory.\n");
	else if (msg_code == MSG_OPEN_FAIL)
		ft_printfd(STDERR_FILENO, "Error\nCannot open file.\n");
	else if (msg_code == MSG_MAP_FAIL) // generic to be implemented
		ft_printfd(STDERR_FILENO, "Error\nMap issues.\n");

	}

int	cleanup_and_exit(t_data *data, int exit_code, int msg_code)
{
	if (msg_code)
		print_err_mess(msg_code);
	if (data->mlx && data->mlx->img)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	if (data->mlx && data->mlx->win)
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	if (data->mlx && data->mlx->mlx)
	{
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx->mlx);
	}
	if (data->mlx)
		free(data->mlx);
	if (data->map)
		free(data->map);
	if (data->player)
		free(data->player);
	exit(exit_code);
}

int	handle_close_window(t_data *data)
{
	cleanup_and_exit(data, EXIT_SUCCESS, MSG_NONE);
	return (0);
}
