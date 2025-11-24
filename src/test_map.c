/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:43:20 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/24 16:43:31 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_test_map(t_data *data)
{
	int	i;
	int	j;

	data->map_width = 10;
	data->map_height = 10;
	for (i = 0; i < data->map_height; i++)
	{
		for (j = 0; j < data->map_width; j++)
		{
			if (i == 0 || i == data->map_height - 1 || j == 0 || j == data->map_width - 1)
				data->map[i][j] = 1; // Wall
			else
				data->map[i][j] = 0; // Empty space
		}
	}
}
