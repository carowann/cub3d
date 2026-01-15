/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:53:15 by cwannhed          #+#    #+#             */
/*   Updated: 2026/01/15 17:57:28 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	load_single_tex(t_tex *tex, t_mlx *mlx, char *tex_path)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx,
			tex_path, &tex->width, &tex->height);
	if (!tex->img)
		return (FAILURE);
	tex->addr = (int *)mlx_get_data_addr(tex->img,
			&tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (!tex->addr)
		return (FAILURE);
	return (SUCCESS);
}

void	load_all_tex(t_data *data, t_mlx *mlx)
{
	if (load_single_tex(&mlx->tex[0], mlx, data->tex_path[0]) != SUCCESS
		|| load_single_tex(&mlx->tex[1], mlx, data->tex_path[1]) != SUCCESS
		|| load_single_tex(&mlx->tex[2], mlx, data->tex_path[2]) != SUCCESS
		|| load_single_tex(&mlx->tex[3], mlx, data->tex_path[3]) != SUCCESS)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_FAIL_LOAD_TEX);
}
