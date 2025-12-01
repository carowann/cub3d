/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2025/12/01 17:18:22 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int fd_map;

	fd_map = check_input(argc, argv);

	init_data(&data);

	if (read_cub(&data, fd_map) == -1)
    {
		printf("read map error");
	}
	// parse input and map
	// parse arguments and map file
	test_map(&data);  // mappa hardcoded
	test_player(data.player); // player hardcoded
	game_loop(&data);
	return (0);
}
