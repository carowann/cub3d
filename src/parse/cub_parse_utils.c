/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:49:45 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/29 14:56:46 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	skip_spaces(&s);
	if (ft_strchr("01NSEW ", *s))
		return (true);
	return (false);
}

static bool	ok_colour_value(char **value)
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
			if (!ft_isdigit(value[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

size_t	validate_colours(t_data d, char *colour)
{
	int		i;
	int		rgb[3];
	char	**value;

	i = 1;
	while (ft_isspace(colour[i]))
		i++;
	value = ft_split(&colour[i], ',');
	if (!value)
		return (free(colour),
			cleanup_and_exit(&d, EXIT_FAILURE, MSG_MALL_FAIL));
	i = 0;
	while (value[i] != NULL)
		i++;
	if (i != 3 || !ok_colour_value(value))
		return (free_matrix((void **)value), free(colour),
			cleanup_and_exit(&d, EXIT_FAILURE, MSG_COL_FAIL));
	rgb[0] = ft_atoi(value[0]);
	rgb[1] = ft_atoi(value[1]);
	rgb[2] = ft_atoi(value[2]);
	free_matrix((void **)value);
	if (rgb[0] < 0 || rgb[0] > 255 || (rgb[1] < 0
			|| rgb[1] > 255) || (rgb[2] < 0 || rgb[2] > 255))
		return (free(colour), cleanup_and_exit(&d, EXIT_FAILURE, MSG_COL_FAIL));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

char	*clean_path(t_data *data, char *s)
{
	int		i;
	int		fd;
	char	*path;
	char	*temp;

	i = 2;
	while (s[i] && ft_isspace(s[i]))
		i++;
	path = ft_strdup(&s[i]);
	temp = path;
	if (!path)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_MALL_FAIL);
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		free(s);
		free(path);
		cleanup_and_exit(data, EXIT_FAILURE, MSG_FAIL_LOAD_TEX);
	}
	close (fd);
	return (path);
}
