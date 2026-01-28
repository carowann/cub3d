
// void	allocate_map(t_data *data, t_list *lines)
// {
// 	int		x;
// 	int		y;
// 	int		len;
// 	t_list	*tmp;

// 	data->map->grid = malloc(sizeof(char *) * (data->map->height + 1));
// 	tmp = lines;
// 	y = 0;
// 	while (tmp)
// 	{
// 		x = 0;
// 		char *content = (char *)tmp->content;
// 		len = ft_strlen(content);
// 		data->map->grid[y] = malloc(sizeof(char) * (data->map->width + 1));
// 		while (x < len)
// 		{
// 			data->map->grid[y][x] = content[x];
// 			x++;
// 		}
// 		while (x < data->map->width)
// 		{
// 			data->map->grid[y][x] = ' ';
// 			x++;
// 		}
// 		data->map->grid[y][x] = '\0';
// 		tmp = tmp->next;
// 		y++;
// 	}
// 	data->map->grid[y] = NULL;
// 	print_mess(MSG_MAP_GRID, SUCCESS);
// 	ft_lstclear(&lines, free);
// }

// static void	handle_cub(t_data *data, int fd)
// {
// 	int		id;
// 	char	*line;

// 	id = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 		{
// 			data->finished_reading = true;
// 			break ;
// 		}
// 		if (ft_strchr(line, '\n'))
// 			*ft_strchr(line, '\n') = '\0';
// 		handle_line(data, line, &id);
// 		// if (line_is_empty(line) && id < 6)
// 		// {
// 		// 	free(line);
// 		// 	continue ;
// 		// }
// 		// if (line_is_ids(line))
// 		// {
// 		// 	if (id >= 6)
// 		// 	{
// 		// 		while (line)
// 		// 		{
// 		// 			free(line);
// 		// 			line = get_next_line(fd);
// 		// 		}
// 		// 		cleanup_and_exit(data, EXIT_FAILURE, MSG_CUB_FAIL_03);
// 		// 	}
// 		// 	read_ids(data, line);
// 		// 	id++;
// 		// }
// 		// else if (id < 6 && !line_is_ids(line))
// 		// {
// 		// 	free(line);
// 		// 	cleanup_and_exit(data, EXIT_FAILURE, "id cacca\n");
// 		// }
// 		// else if (id == 6 && line_is_map(line))
// 		// 	add_line(line, data);
// 		free(line);
// 	}
// }