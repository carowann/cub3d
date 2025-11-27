/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:27:45 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/27 14:07:28 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	print_error_message(char *msg)
{
	ft_printfd(STDERR_FILENO, "%s", msg);
}

static void	free_mlx(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
}

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->grid)
		free_matrix((void **)map->grid);
	free(map);
}

void	free_matrix(void **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	cleanup_and_exit(t_data *data, int exit_code, char *msg)
{
	int	i;

	i = 0;
	if (msg)
		print_error_message(msg);
	if (data->mlx)
		free_mlx(data->mlx);
	if (data->map)
		free_map(data->map);
	if (data->player)
		free(data->player);
	exit(exit_code);
}

int	handle_close_window(t_data *data)
{
	cleanup_and_exit(data, EXIT_SUCCESS, NULL);
	return (0);
}
