/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/29 11:42:34 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: REMOVE. NORME: KO
#include "../includes/cub3d.h"

// void    print_map_debug(t_data *data, t_list *lines)
// {
//     int     y;
//     t_list  *tmp;

//     printf("\n================ DEBUG MAPPA ================\n");

//     // 1. STAMPA MAPPA "GREZZA" (Dalla lista)
//     printf("--- 1. CONTENUTO LISTA (Grezzo dal .cub) ---\n");
//     tmp = lines;
//     y = 0;
//     while (tmp)
//     {
//         // Usiamo [%s] per vedere se ci sono spazi o newline invisibili
//         printf("%2d: [%s]\n", y, (char *)tmp->content);
//         tmp = tmp->next;
//         y++;
//     }

//     // 2. STAMPA MATRICE ALLOCATA (Dopo allocate_map con padding)
//     printf("\n--- 2. MATRICE ALLOCATA (%d x %d) ---\n",
//             data->map->width, data->map->height);
//     if (!data->map->grid)
//         printf("Matrice non ancora allocata.\n");
//     else
//     {
//         y = 0;
//         while (data->map->grid[y])
//         {
//             printf("%2d: |%s|\n", y, data->map->grid[y]);
//             y++;
//         }
//     }
//     printf("=============================================\n\n");
// }

int	main(int argc, char *argv[])
{
	t_data	data;

	data = (t_data){0};
	data.fd = check_input(argc, argv);
	init_data(&data);
	read_cub(&data);
	init_mlx(data.mlx, &data);
	load_all_tex(&data, data.mlx);
	game_loop(&data);
	return (0);
}
