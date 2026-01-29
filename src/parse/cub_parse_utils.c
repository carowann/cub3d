/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:49:45 by giomastr          #+#    #+#             */
/*   Updated: 2026/01/29 11:47:31 by cwannhed         ###   ########.fr       */
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
		return (free(colour), cleanup_and_exit(&data, EXIT_FAILURE, MSG_MALL_FAIL));
	row_count = 0;
	while (value[row_count] != NULL)
		row_count++;
	if (row_count != 3)
		return (free_matrix((void **)value), free(colour),
			cleanup_and_exit(&data, EXIT_FAILURE, MSG_COL_FAIL));
	if (!ok_colour_value(value))
		return(free_matrix((void **)value), free(colour), cleanup_and_exit(&data, EXIT_FAILURE, MSG_COL_FAIL));
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
