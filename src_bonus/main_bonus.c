/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2026/02/03 10:56:51 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	data = (t_data){0};
	data.fd = check_input(argc, argv);
	init_data(&data);
	read_cub(&data);
	init_mlx(data.mlx, &data);
	load_all_tex(&data, data.mlx);
	start_mlx(data);
	game_loop(&data);
	return (0);
}
