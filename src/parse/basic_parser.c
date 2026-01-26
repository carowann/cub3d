/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/01/26 16:17:26 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// TODO: REMOVE. NORME:ok
// check basic stuff - input, file extension, handle ids
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
	int	fd_map;

	if (argc != 2)
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_N_ARGS);
	if (!is_cub_file(argv[1]))
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_CUB_EXT);
	fd_map = open(argv[1], O_DIRECTORY);
	if (fd_map > 0)
	{
		close(fd_map);
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_IS_DIR);
	}
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_OPEN_FAIL);
	print_mess(MSG_INPUT_OK, SUCCESS);
	return (fd_map);
}

t_id	get_id_line(char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
		return (ID_NO);
	if (ft_strncmp(str, "SO", 2) == 0)
		return (ID_SO);
	if (ft_strncmp(str, "WE", 2) == 0)
		return (ID_WE);
	if (ft_strncmp(str, "EA", 2) == 0)
		return (ID_EA);
	if (ft_strncmp(str, "F", 1) == 0)
		return (ID_FL);
	if (ft_strncmp(str, "C", 1) == 0)
		return (ID_CE);
	return (-1);
}
