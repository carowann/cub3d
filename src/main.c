/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:07 by giomastr          #+#    #+#             */
/*   Updated: 2025/12/04 11:37:42 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void)
{
	t_data	data;

	//parse arguments and map file
	init_data(&data);
	set_textures_path(&data);
	load_all_textures(&data);
	test_map(&data);  // mappa hardcoded
	game_loop(&data);
	return (0);
}
