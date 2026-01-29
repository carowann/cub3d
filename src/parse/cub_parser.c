/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:55:24 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/29 14:36:17 by cwannhed         ###   ########.fr       */
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
}

static void	handle_line(t_data *data, char *line, int *id)
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
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_04);
	}
	else if (*id == 6 && line_is_map(line))
		add_line(line, data);
}

static void	handle_cub(t_data *data)
{
	int		id;
	char	*line;

	id = 0;
	while (1)
	{
		line = get_next_line(data->fd);
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

void	read_cub(t_data *data)
{
	if (data->fd < 0 || !data || !data->map)
		return ;
	handle_cub(data);
	if (!data->tex_path[0] || !data->tex_path[1]
		|| !data->tex_path[2] || !data->tex_path[3])
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_01);
	if (!data->map->floor_color_found || !data->map->ceiling_color_found)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_02);
	print_mess(MSG_CUB_OK, SUCCESS);
	allocate_map(data, data->map->lines);
	validate_map(data);
	close(data->fd);
}
