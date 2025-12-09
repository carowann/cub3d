/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:53:15 by cwannhed          #+#    #+#             */
/*   Updated: 2025/12/09 10:52:03 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void set_textures_path(t_data *data)
{
	data->textures_path[0] = "textures/north.xpm";
	data->textures_path[1] = "textures/south.xpm";
	data->textures_path[2] = "textures/west.xpm";
	data->textures_path[3] = "textures/east.xpm";
}

static int load_single_tex(t_textures *tex, t_mlx *mlx, char *tex_path)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx, tex_path, &tex->width, &tex->height);
	if (!tex->img)
		return (FAILURE);
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (!tex->addr)
		return (FAILURE);
	return (SUCCESS);
}

void load_all_textures(t_data *data, t_mlx *mlx)
{
	if (load_single_tex(&mlx->textures[0], mlx, data->textures_path[0]) != SUCCESS
		|| load_single_tex(&mlx->textures[1], mlx, data->textures_path[1]) != SUCCESS
		|| load_single_tex(&mlx->textures[2], mlx, data->textures_path[2]) != SUCCESS
		|| load_single_tex(&mlx->textures[3], mlx, data->textures_path[3]) != SUCCESS)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_FAIL_LOAD_TEX);
}
