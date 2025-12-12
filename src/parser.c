/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:17:51 by giomastr          #+#    #+#             */
/*   Updated: 2025/12/12 11:50:09 by cwannhed         ###   ########.fr       */
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
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_N_ARGS);
	if (!is_cub_file(argv[1]))
		cleanup_and_exit(NULL, EXIT_FAILURE, MSG_CUB_EXT);
	return (0);
}

void	read_map(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printfd(STDERR_FILENO, "Error\nFailed to open file: %s\n", path);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		free(line);
	}
	close(fd);
}
