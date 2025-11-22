/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:51 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/22 15:21:48 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_cub_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) == 0)
		return (1);
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printfd(STDERR_FILENO, "Error\nInvalid number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	if (!is_cub_file(argv[1]))
	{
		ft_printfd(STDERR_FILENO, "Error\nInvalid file extension. Expected .cub\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}