/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:01:42 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/15 14:33:23 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ONLY maze map part

#include "../../includes/cub3d.h"

void	add_line(char *line, t_data *data)
{
	t_list	*new_node;

	new_node = ft_lstnew(ft_strtrim(line, "\n")); //trim line then save
	if (!new_node)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	if ((int)ft_strlen(new_node->content) >= data->map->width) // find max length
		data->map->width = ft_strlen(new_node->content); // becomes redundant if in alloc?
	ft_lstadd_back(&data->map->lines, new_node);
	data->map->height++;
	// printf("add_line check: Height: %d, Width: %d\n", data->map->height, data->map->width);
	return ;
}
void    allocate_map(t_data *data, t_list *lines)
{
	int x;
	int y;
	int len;
	t_list *tmp = lines;

	data->map->grid = malloc(sizeof(char *) * (data->map->height + 1));
	y = 0;
	while (tmp)
	{
		x = 0;
		char *content = (char *)tmp->content;
		len = ft_strlen(content);
		data->map->grid[y] = malloc(sizeof(char) * (data->map->width + 1));
		while (x < len)
		{
			data->map->grid[y][x] = content[x];
			x++;
		}
		while (x < data->map->width)
		{
			data->map->grid[y][x] = ' '; // Padding con spazio
			x++;
		}
		data->map->grid[y][x] = '\0';
		tmp = tmp->next;
		y++;
	}
	data->map->grid[y] = NULL;
	print_map_debug(data, lines);
	free_list(lines);
}

char	**copy_matrix(char **grid, int height)
{
	char **copy;
	int    i;

	i = 0;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	while (i < height)
	{
		copy[i] = ft_strdup(grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)// Libera se strdup fallisce - chat sugg
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// Requires passing integer coordinates (x, y) and map dimensions (max_x, max_y)
int	maze_fill(char **map, int x, int y, int max_x, int max_y)
{
	if (x < 0 || y < 0 || x >= max_x || y >= max_y)
		return (0); // out of bound

	char pos = map[y][x];
	if (pos == '1' || pos == 'V')
		return (1); // visiting ALL spaces
	if (pos == ' ')
		return (print_err_mess(MSG_MAP_FAIL), 2); // leaked space
	map[y][x] = 'V'; // Visited
	if (!maze_fill(map, x, y - 1, max_x, max_y)) // North
		return (0);
	if (!maze_fill(map, x, y + 1, max_x, max_y)) // South
		return (0);
	if (!maze_fill(map, x - 1, y, max_x, max_y)) // West
		return (0);
	if (!maze_fill(map, x + 1, y, max_x, max_y)) // East
		return (0);
	return (1); // Success
}

int	check_lines(int rows, int cols, char **map_mat)// change into count nodes*
{
	int	i;
	int	row_len;

	i = 0;
	if (rows <= 3 || cols <= 3)
	{
		return (print_err_mess(MSG_MAP_FAIL), 0);
	}
	while (i < rows)
	{
		row_len = ft_strlen(map_mat[i]);
		if (cols != row_len)
			return (print_err_mess(MSG_MAP_FAIL), 0);
		i++;
	}
	return (1);
}