/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:55:24 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/27 12:46:30 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	read_ids(t_data *data, char *line)
{
	char	*value;

	value = NULL;
	skip_spaces(&line);
	if (line)
	{
		value = ft_strtrim(line, "\n");
		// free(line);
		if (!value)
		{
			free(line);
			cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
		}
	}
	if (value && ft_strncmp(value, "NO", 2) == 0)
		data->tex_path[NORTH] = clean_path(data, value);
	else if (value && ft_strncmp(value, "SO", 2) == 0)
		data->tex_path[SOUTH] = clean_path(data, value);
	else if (value && ft_strncmp(value, "WE", 2) == 0)
		data->tex_path[WEST] = clean_path(data, value);
	else if (value && ft_strncmp(value, "EA", 2) == 0)
		data->tex_path[EAST] = clean_path(data, value);
	else if (value && ft_strncmp(value, "F", 1) == 0)
	{
		data->map->floor_color = validate_colours(*data, value);
		print_mess(MSG_F_OK, SUCCESS);
		data->map->floor_color_found = true;
	}
	else if (value && ft_strncmp(value, "C", 1) == 0)
	{
		data->map->ceiling_color = validate_colours(*data, value);
		print_mess(MSG_C_OK, SUCCESS);
		data->map->ceiling_color_found = true;
	}
	else
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_00);
	return ;
}

void	read_cub(t_data *data, int fd)
{
	char	*line;
	int		id;

	line = 0;
	if (fd < 0 || !data || !data->map)
		return ;
	id = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			data->finished_reading = true;
			break;
		}
		// if (ft_strchr(line, '\n'))
		// 	*ft_strchr(line, '\n') = '\0';
		if (line_is_empty(line) && id < 6)
		{
			free(line);
			continue ;
		}
		if (line_is_ids(line))
		{
			if (id >= 6)
			{
				while (line)
				{
					free(line);
					line = get_next_line(fd);
				}
				cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_03);
			}
			read_ids(data, line);
			id++;
		}
		else if (id < 6 && !line_is_ids(line))
		{
			free(line);
			cleanup_and_exit(data, EXIT_FAILURE, "id cacca\n"); //se text dentro mappa o dopo o mancante
		}
		else if (id == 6 && line_is_map(line))
			add_line(line, data);
		free(line);
	}
	if (!data->tex_path[0] || !data->tex_path[1] || !data->tex_path[2] || !data->tex_path[3])
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_01);
	if (!data->map->floor_color_found || !data->map->ceiling_color_found)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_02);
	print_mess(MSG_CUB_OK, SUCCESS);
	allocate_map(data, data->map->lines);
	validate_map(data);
	close(fd);
}
