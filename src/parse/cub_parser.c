/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:55:24 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/16 14:54:25 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	line_is_empty(char *s)
{
	while (*s && ft_isspace(*s))
		return (true);
	return (false);
}

bool	line_is_ids(char *s)
{
	int	id;

	id = get_id_line(s);
	if (id == -1)
		return (false);
	return (true);
}

bool	line_is_map(char *s)
{
	int	 i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (ft_strchr("01NSEW ", s[i]))
				return (true);
	return (false);
}

int	validate_colours(t_data *data, char *colour) // analyse value
{
	int		r;
	int		g;
	int		b;
	int		row_count;
	char	**value;

	while (!ft_isdigit(*colour))
		colour++;
	value = ft_split(colour, ',');
	if (!value)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	row_count = 0;
	while (value[row_count] != NULL)
		row_count++;
	if (row_count != 3)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_COL_FAIL);
	r = ft_atoi(value[0]);
	g = ft_atoi(value[1]);
	b = ft_atoi(value[2]);
	free_matrix((void**)value);
	if (r < 0 || r > 255 || (g < 0 || g > 255) || (b < 0 || b > 255))
		cleanup_and_exit(data, EXIT_FAILURE, MSG_COL_FAIL);
	return ((r << 16) | (g << 8) | b);
}

char 	*clean_path(t_data *data, char *s)
{
	int i;
	char *path;
	char *temp;

	i = 2;
	while (s[i] && ft_isspace(s[i]))
		i++;
	path = ft_strdup(&s[i]);
	temp = path;
	// free(path);
	if (!path)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	path = ft_strtrim(temp, "\n");
	if (!path)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	return (path);
}

void    read_ids(t_data *data, char *line)
{
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
		data->map->floor_color = validate_colours(data, line);
		ft_printfd(STDOUT_FILENO, GREEN "✅ Validated floor color\n" RESET);
		data->map->floor_color_found = true;
	}
	else if (line && ft_strncmp(line, "C", 1) == 0)
	{
		data->map->ceiling_color = validate_colours(data, line);
		ft_printfd(STDOUT_FILENO, GREEN "✅ Validated ceiling color\n" RESET);
		data->map->ceiling_color_found = true;
	}
	else
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_00);
	return ;
}

void    read_cub(t_data *data, int fd)
{
	char *line;
	int id;

	line = 0;
	if (fd < 0 || !data || !data->map)
		return ;
	id =  0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_is_empty(line) && id < 6)
		{
			free(line);
			continue ;
		}
		if (line_is_ids(line))
		{
			if (id >= 6)
			{
				free(line);
				cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_03);
			}
			read_ids(data, line);
			id++;
		}
		else if (id >= 6 && line_is_map(line))
			add_line(line, data);
		free(line);
	}
	if (!data->tex_path[0] || !data->tex_path[1] || !data->tex_path[2] || !data->tex_path[3])
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_01);
	if (!data->map->floor_color_found || !data->map->ceiling_color_found)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_02);
	ft_printfd(STDOUT_FILENO, GREEN "✅ Read .cub file\n" RESET);
	allocate_map(data, data->map->lines);
	validate_map(data);
	close(fd);
}
