
#include "cubed.h"

int	basic_check(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 4 && ft_strncmp(str + (len - 4), ".cub", 4) == 0)
	{
		return (ft_putstr_fd("Extension -> Correct\n", 1), 1);
	}
	else
		return (ft_putstr_fd("Extension -> Fail\n", 2), 0);
	return (0);
}

void	floodfill(t_mlx_win *window, char **map_mat, t_coord curr)
{
	const char	pos = map_mat[curr.y][curr.x];

	if (pos == '1' || pos == 'G')
		return ;
	if (pos == 'C')
		window->map.prcdio++;
	if (pos == 'E')
		window->map.prcmdnna++;
	map_mat[curr.y][curr.x] = 'G';
	floodfill(window, map_mat, (t_coord){curr.x, curr.y - 1});
	floodfill(window, map_mat, (t_coord){curr.x, curr.y + 1});
	floodfill(window, map_mat, (t_coord){curr.x - 1, curr.y});
	floodfill(window, map_mat, (t_coord){curr.x + 1, curr.y});
}

int	ff_check(t_mlx_win *window)
{
	char	**copy;

	copy = mat_copy(window->map.map_mat, window->size.y);
	if (!copy)
		return (0);
	floodfill(window, copy, window->map.player);
	ft_free_matrix(copy);
	if (window->map.ff_exit != 1)
		return (0);
	if (window->map.collectible != window->map.ff_collect)
		return (0);
	return (1);
}

void	map_checks(t_mlx_win *window, int rows, int cols)
{
	rows = window->size.y;
	cols = window->size.x;
	if (check_lines(rows, cols, window->map.map_mat) == 0)
		ft_exit(window, "Error - What's happening with those lines\n", 13);
	if (check_elements(rows, cols, window) == 0)
		ft_exit(window, "Error - Wrong elements in map\n", 13);
	if (count_elements(rows, cols, window->map.map_mat, 'P') != 1)
		ft_exit(window, "Error - What in the Dolphin is going on?\n", 13);
	window->map.collectible = count_elements(rows, cols,
			window->map.map_mat, 'C');
	if (window->map.collectible <= 0)
		ft_exit(window, "Error - Where is the DATA?\n", 13);
	if (count_elements(rows, cols, window->map.map_mat, 'E') != 1)
		ft_exit(window, "Error - Cannot escape, \
		cannot come out...MAMAAA\n", 13);
	if (check_walls(window->map.map_mat, rows, cols) == 0)
		ft_exit(window, "Error - Breach in the walls\n", 13);
	if (!ff_check(window))
		ft_exit(window, "Error - OVERFLOODfill", 13);
}

int	check_if_dir(t_mlx_win *window, int argc, char *argv[])
{
	int		fd_map;

	if (argc != 2)
		ft_exit(window, "Error - What are you doing babe\n", 1);
	if (basic_check(argv[1]) == 0)
		ft_exit(window, "Error - Wrong extension\n", 2);
	fd_map = open(argv[1], O_DIRECTORY);
	if (fd_map > 0)
	{
		close(fd_map);
		ft_exit(window, "Error - It's a directory\n", 3);
	}
	fd_map = open(argv[1], O_RDONLY);
	if (fd_map < 0)
		ft_exit(window, "Error - Can't open file\n", 4);
	return (fd_map);
}

int	check_lines(int rows, int cols, char **map_mat)//2
{
	int	i;
	int	row_len;

	i = 0;
	if (rows <= 3 || cols <= 3)
	{
		return (ft_printf("Map too small, wrong vibes\n", 2), 0);
	}
	while (i < rows)
	{
		row_len = ft_strlen(map_mat[i]);
		if (cols != row_len)
		{
			return (ft_printf("different lines, wrong vibes\n", 2), 0);
		}
		i++;
	}
	return (1);
}

int	check_walls(char **map_mat, int rows, int cols)
{
	int	i;
	int	j;
	int	last_col;

	i = 0;
	last_col = cols - 1;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == last_col)
			{
				if (map_mat[i][j] != '1')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	count_elements(int rows, int cols, char **map, char to_check)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == to_check)
			{
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	check_elements(int rows, int cols, t_mlx_win *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->map.map_mat;
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (map[i][j] != 'C' && map[i][j] != 'E' && map[i][j] != 'P'
			&& map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N')
				return (0);
			if (map[i][j] == 'P')
				game->map.player = (t_coord){j, i};
			if (map[i][j] == 'E')
				game->map.exit = (t_coord){j, i};
		}
	}
	return (1);
}