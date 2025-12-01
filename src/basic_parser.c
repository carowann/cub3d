/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:51 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/29 19:06:24 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// when we get here everything is checked already, we know file can be opend from folder



// int	read_map(t_data *data, int fd)
// {

// 	while (1)
// 	{
// 		char *line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		data->map->grid = add_to_grid(data->map->grid, line);
// 		free(line);
// 	}
// 	close(fd);
// 	// You should add validation checks here (e.g., player starting position, walls)
//     // if map is invalid: return (-1);
// 	return (0);
// }
