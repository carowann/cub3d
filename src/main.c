/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/15 16:35:32 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    print_map_debug(t_data *data, t_list *lines)
{
    int     y;
    t_list  *tmp;

    printf("\n================ DEBUG MAPPA ================\n");

    // 1. STAMPA MAPPA "GREZZA" (Dalla lista)
    printf("--- 1. CONTENUTO LISTA (Grezzo dal .cub) ---\n");
    tmp = lines;
    y = 0;
    while (tmp)
    {
        // Usiamo [%s] per vedere se ci sono spazi o newline invisibili
        printf("%2d: [%s]\n", y, (char *)tmp->content);
        tmp = tmp->next;
        y++;
    }

    // 2. STAMPA MATRICE ALLOCATA (Dopo allocate_map con padding)
    printf("\n--- 2. MATRICE ALLOCATA (%d x %d) ---\n",
            data->map->width, data->map->height);
    if (!data->map->grid)
        printf("Matrice non ancora allocata.\n");
    else
    {
        y = 0;
        while (data->map->grid[y])
        {
            printf("%2d: |%s|\n", y, data->map->grid[y]);
            y++;
        }
    }
    printf("=============================================\n\n");
}
int	main(int argc, char *argv[])
{
	t_data	data;
	int fd_map;

    data = (t_data){0};
	fd_map = check_input(argc, argv);
	init_data(&data);
	read_cub(&data, fd_map);
	init_mlx(data.mlx, &data);
	printf("path: %s", data.tex_path[0]);
	printf("path: %s", data.tex_path[1]);
	printf("path: %s", data.tex_path[2]);
	printf("path: %s", data.tex_path[3]);
	printf("path: %zu", data.map->ceiling_color);
	printf("path: %zu", data.map->floor_color);
	load_all_tex(&data, data.mlx);
	game_loop(&data);
	return (0);
}
