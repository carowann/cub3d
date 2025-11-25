/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:51 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/25 14:51:04 by giomastr         ###   ########.fr       */
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
	int		fd_map;

	if (argc != 2)
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_N_ARGS);
	if (!is_cub_file(argv[1]))
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_CUB_EXT);
	// return (0);
	fd_map = open(argv[1], O_DIRECTORY);
	if (fd_map > 0)
	{
		close(fd_map);
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_IS_DIR);
	}
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_OPEN_FAIL);
	return (fd_map); // CHECK THIS AS FROM SOLONG
}
// when we get here everything is checked already, we know file can be opend from folder
void	read_map(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0) // check later whether to remove or not
	{
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_OPEN_FAIL);
		exit(EXIT_FAILURE);
	}
	//read line by line
	//store lines in data structure
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		//process line (e.g., store in structure)
		free(line);
	}
	close(fd);
}
