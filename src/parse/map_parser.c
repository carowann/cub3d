/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:01:42 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/29 12:43:40 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: REMOVE. NORME: KO
#include "../../includes/cub3d.h"

void	add_line(char *line, t_data *data)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_strtrim(line, "\n"));
	if (!new_node)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	if ((int)ft_strlen(new_node->content) >= data->map->width)
		data->map->width = ft_strlen(new_node->content);
	ft_lstadd_back(&data->map->lines, new_node);
	data->map->height++;
	return ;
}

static char	*fill_grid_line(char *content, int width)
{
	char	*line;
	int		i;
	int		len;

	line = malloc(sizeof(char) * (width + 1));
	if (!line)
		return (NULL);
	len = ft_strlen(content);
	i = 0;
	while (i < width)
	{
		if (i < len)
			line[i] = content[i];
		else
			line[i] = ' ';
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	allocate_map(t_data *data, t_list *lines)
{
	int		y;
	t_list	*tmp;

	data->map->grid = malloc(sizeof(char *) * (data->map->height + 1));
	if (!data->map->grid)
		return ;
	tmp = lines;
	y = 0;
	while (tmp)
	{
		data->map->grid[y] = fill_grid_line((char *)tmp->content,
				data->map->width);
		tmp = tmp->next;
		y++;
	}
	data->map->grid[y] = NULL;
	print_mess(MSG_MAP_GRID, SUCCESS);
	ft_lstclear(&lines, free);
}

int	maze_fill(char **map, int x, int y, t_data d)
{
	char	pos;

	if (x < 0 || y < 0 || x >= d.map->width || y >= d.map->height)
		return (0);
	pos = map[y][x];
	if (pos == '1' || pos == 'V')
		return (1);
	if (pos == ' ')
		return (0);
	map[y][x] = 'V';
	if (!maze_fill(map, x, y - 1, d))
		return (0);
	if (!maze_fill(map, x, y + 1, d))
		return (0);
	if (!maze_fill(map, x - 1, y, d))
		return (0);
	if (!maze_fill(map, x + 1, y, d))
		return (0);
	return (1);
}

int	check_lines(int rows, int cols, char **map_mat)
{
	int	i;
	int	row_len;

	i = 0;
	if (rows <= 3 || cols <= 3)
	{
		print_mess(MSG_MAP_FAIL_00, FAILURE);
		return (0);
	}
	while (i < rows)
	{
		row_len = ft_strlen(map_mat[i]);
		if (cols != row_len)
		{
			print_mess(MSG_MAP_FAIL_02, FAILURE);
			return (0);
		}
		i++;
	}
	return (1);
}
