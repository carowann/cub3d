/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:43:20 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/25 11:55:04 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_test_map(t_data *data)
{
	int	i;
	int	j;

	data->map->width = 10;
	data->map->height = 10;
	for (i = 0; i < data->map->height; i++)
	{
		for (j = 0; j < data->map->width; j++)
		{
			if (i == 0 || i == data->map->height - 1 || j == 0 || j == data->map->width - 1)
				data->map->grid[i][j] = 1; // Wall
			else
				data->map->grid[i][j] = 0; // Empty space
		}
	}
}
