/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:01:42 by giomastr          #+#    #+#             */
/*   Updated: 2025/11/25 14:52:49 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// floodfill will be checking:
// void	maze_fill(t_mlx_win *window, char **map_mat, t_coord curr)
// {
// 	const char	pos = map_mat[curr.y][curr.x];

// 	if (pos == '1' || pos == 'G')
// 		return ;
// 	map_mat[curr.y][curr.x] = 'G';
// 	maze_fill(window, map_mat, (t_coord){curr.x, curr.y - 1});
// 	maze_fill(window, map_mat, (t_coord){curr.x, curr.y + 1});
// 	maze_fill(window, map_mat, (t_coord){curr.x - 1, curr.y});
// 	maze_fill(window, map_mat, (t_coord){curr.x + 1, curr.y});
// }

bool	viable_map(t_data *cubd)
{
	maze_fill();
	//cleanup
	if (viable)
		return (true);
	else
		return (false);
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

int	check_walls(char **map_mat, int rows, int cols) // Should be good
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




// for ref ONLY

// int	ft_exit(t_mlx_win *window, char *str, int flag)
// {
// 	if (str)
// 		ft_putstr_fd(str, 2);
// 	ft_putstr_fd("bye", 2);
// 	free_exit(window, flag);
// 	exit(flag);
// }