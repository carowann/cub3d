/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2025/12/09 14:37:12 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int fd_map;

	fd_map = check_input(argc, argv);
	init_data(&data);
	read_cub(&data, fd_map);
	printf("path: %s", data.textures_path[0]);
	printf("path: %s", data.textures_path[1]);
	printf("path: %s", data.textures_path[2]);
	printf("path: %s", data.textures_path[3]);
	printf("path: %d", data.map->ceiling_color);
	printf("path: %d", data.map->floor_color);

	// read_cub(&data, fd_map);
	// parse input and map
	// parse arguments and map file
	// test_map(&data);  // mappa hardcoded
	// test_player(data.player); // player hardcoded
	// game_loop(&data);
	return (0);
}
