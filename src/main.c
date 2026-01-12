/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/12 16:15:16 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map_debug(t_data *data)
{
	int	y;

	if (!data || !data->map || !data->map->grid)
	{
		printf("Mappa non ancora allocata.\n");
		return ;
	}
	printf("\n--- DEBUG MAPPA (%d x %d) ---\n", data->map->width, data->map->height);
	y = 0;
	while (data->map->grid[y])
	{
		// Stampiamo un numero di riga e un '|' per vedere l'inizio
		printf("%2d: |", y);

		// Stampiamo la riga
		printf("%s", data->map->grid[y]);

		// Stampiamo un '|' per vedere la fine della riga (dopo il padding)
		printf("|\n");
		y++;
	}
	printf("-----------------------------\n\n");
}
int	main(int argc, char *argv[])
{
	t_data	data;
	int fd_map;

	fd_map = check_input(argc, argv);
	init_data(&data);
	read_cub(&data, fd_map);
	printf("path: %s", data.tex_path[0]);
	printf("path: %s", data.tex_path[1]);
	printf("path: %s", data.tex_path[2]);
	printf("path: %s", data.tex_path[3]);
	printf("path: %d", data.map->ceiling_color);
	printf("path: %d", data.map->floor_color);
	game_loop(&data);
	return (0);
}
