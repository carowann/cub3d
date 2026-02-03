/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:35:52 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/03 16:49:09 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	line_is_empty(char *s)
{
	while (s && *s)
	{
		if (!ft_isspace(*s))
			return (false);
		s++;
	}
	return (true);
}

void	print_mess(char *msg, int code)
{
	if (code == SUCCESS)
		ft_printfd(STDOUT_FILENO, GREEN "%s" RESET, msg);
	else if (code == FAILURE)
	{
		ft_printfd(STDERR_FILENO, RED "❌ Error\n");
		ft_printfd(STDERR_FILENO, "%s" RESET, msg);
	}
}

void	kill_get_next_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

double	get_current_time(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != SUCCESS)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_TIME_FAIL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	skip_spaces(char **line)
{
	while (*line && **line && ft_isspace(**line))
		(*line)++;
}
