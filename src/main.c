/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/22 15:40:27 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	// void	*mlx;
	// void	*win;

	//validation  and parsing of arguments
	check_input(argc, argv);
	//parse_scene(argv[1]);
	//validation and parsing of map
	//initialization of mlx and window

	// mlx = mlx_init();
	// if (!mlx)
	// 	return (1);
	// win = mlx_new_window(mlx, 800, 600, "Cub3D");
	// mlx_loop(mlx);

	//event loop
	//cleanup and exit
	return (0);
}
