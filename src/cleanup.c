/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/01/23 13:45:56 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_list(t_list *list)
{
	t_list	*current;
	t_list	*temp;
	int		count;

	if (!list)
		return ;
	current = list;
	count = ft_lstsize(list);
	while (current)
	{
		temp = current->next;
		free(current->content);
		free(current);
		current = temp;
	}
	list = NULL;
}

static void	free_mlx(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->tex->img)
	{
		while (i < 4)
		{
			if (mlx->tex[i].img)
				mlx_destroy_image(mlx->mlx, mlx->tex[i].img);
			i++;
		}
	}
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
// TODO: remove me
void	kill_get_next_line(int fd);

int	cleanup_and_exit(t_data *data, int exit_code, char *msg)
{
	int	i;


	i = 0;
	if (msg)
		print_err_mess(msg);
	if (data)
	{
		if (data->fd >= 0)
			kill_get_next_line(data->fd);
		if (data->mlx)
		free_mlx(data->mlx);
		if (data->map)
			free_map(data->map);
		if (data->player)
			free(data->player);
		if (data->tex_path[0])
			free(data->tex_path[0]);
		if (data->tex_path[1])
			free(data->tex_path[1]);
		if (data->tex_path[2])
			free(data->tex_path[2]);
		if (data->tex_path[3])
			free(data->tex_path[3]);
	}
	exit(exit_code);
}

int	handle_close_window(t_data *data)
{
	cleanup_and_exit(data, EXIT_SUCCESS, NULL);
	return (0);
}
