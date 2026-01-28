/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:49:45 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/28 18:49:40 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: REMOVE. NORME: KO
#include "../../includes/cub3d.h"

bool	line_is_ids(char *s)
{
	int	id;

	skip_spaces(&s);
	id = get_id_line(s);
	if (id == -1)
		return (false);
	return (true);
}

bool	line_is_map(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (ft_strchr("01NSEW ", s[i]))
		return (true);
	return (false);
}

static void	check_colour_value(t_data *data, char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (value[i])
	{
		j = 0;
		while (value[i] && value[i][j])
		{
			printf("current: %c\n", value[i][j]);
			if (ft_isspace(value[i][j]))
				printf("cacca in %d e % d", i, j);
			if (!ft_isdigit(value[i][j]))
				cleanup_and_exit(data, EXIT_FAILURE, MSG_COL_FAIL);
			j++;
		}
		i++;
	}
}

size_t	validate_colours(t_data data, char *colour)
{
	int		i;
	int		rgb[3];
	int		row_count;
	char	**value;

	i = 0;
	while (!ft_isdigit(colour[i]))
		i++;
	value = ft_split(&colour[i], ',');
	if (!value)
		cleanup_and_exit(&data, EXIT_FAILURE, MSG_MALL_FAIL);
	row_count = 0;
	while (value[row_count] != NULL)
		row_count++;
	if (row_count != 3)
		return (free_matrix((void **)value), free(colour),
			cleanup_and_exit(&data, EXIT_FAILURE, MSG_COL_FAIL));
	check_colour_value(&data, value);
	rgb[0] = ft_atoi(value[0]);
	rgb[1] = ft_atoi(value[1]);
	rgb[2] = ft_atoi(value[2]);
	free_matrix((void **)value);
	if (rgb[0] < 0 || rgb[0] > 255 || (rgb[1] < 0 || rgb[1] > 255) || (rgb[2] < 0 || rgb[2] > 255))
		return (free(colour), cleanup_and_exit(&data, EXIT_FAILURE, MSG_COL_FAIL));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

char	*clean_path(t_data *data, char *s)
{
	int		i;
	char	*path;
	char	*temp;

	i = 2;
	while (s[i] && ft_isspace(s[i]))
		i++;
	path = ft_strdup(&s[i]);
	temp = path;
	if (!path)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	return (path);
}
