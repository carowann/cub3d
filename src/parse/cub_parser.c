/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:55:24 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/28 18:41:06 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	read_ids(t_data *data, char *line)
{
	skip_spaces(&line);
	if (line && ft_strncmp(line, "NO", 2) == 0)
		data->tex_path[NORTH] = clean_path(data, line);
	else if (line && ft_strncmp(line, "SO", 2) == 0)
		data->tex_path[SOUTH] = clean_path(data, line);
	else if (line && ft_strncmp(line, "WE", 2) == 0)
		data->tex_path[WEST] = clean_path(data, line);
	else if (line && ft_strncmp(line, "EA", 2) == 0)
		data->tex_path[EAST] = clean_path(data, line);
	else if (line && ft_strncmp(line, "F", 1) == 0)
	{
		data->map->floor_color = validate_colours(*data, line);
		print_mess(MSG_F_OK, SUCCESS);
		data->map->floor_color_found = true;
	}
	else if (line && ft_strncmp(line, "C", 1) == 0)
	{
		data->map->ceiling_color = validate_colours(*data, line);
		print_mess(MSG_C_OK, SUCCESS);
		data->map->ceiling_color_found = true;
	}
	else
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_00);
	return ;
}

static void handle_line(t_data *data, char *line, int *id)
{
	if (line_is_empty(line) && *id < 6)
		return ;
	if (line_is_ids(line))
	{
		if (*id >= 6)
		{
			free(line);
			cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_03);
		}
		read_ids(data, line);
		(*id)++;
	}
	else if (*id < 6)
	{
		free(line);
		cleanup_and_exit(data, EXIT_FAILURE, "id cacca\n");
	}
	else if (*id == 6 && line_is_map(line))
		add_line(line, data);
}

static void	handle_cub(t_data *data, int fd)
{
	int		id;
	char	*line;

	id = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			data->finished_reading = true;
			break ;
		}
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		handle_line(data, line, &id);
		free(line);
	}
}

void	read_cub(t_data *data, int fd)
{
	if (fd < 0 || !data || !data->map)
		return ;
	handle_cub(data, fd);
	if (!data->tex_path[0] || !data->tex_path[1] || !data->tex_path[2] || !data->tex_path[3])
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_01);
	if (!data->map->floor_color_found || !data->map->ceiling_color_found)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_02);
	print_mess(MSG_CUB_OK, SUCCESS);
	allocate_map(data, data->map->lines);
	validate_map(data);
	close(fd);
}
