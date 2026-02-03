/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:35:52 by cwannhed          #+#    #+#             */
/*   Updated: 2026/02/03 10:56:51 by cwannhed         ###   ########.fr       */
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

/*
** Gets the current time in seconds as a floating-point number.
**
** struct timeval breakdown:
** - tv_sec:  seconds since Unix epoch (Jan 1, 1970)
** - tv_usec: microseconds (0-999999) within the current second
**
** Why we need microsecond precision:
** Frame times are very short (e.g., 0.016s at 60 FPS).
** Using only seconds would give us terrible accuracy for delta time
** calculations, making movement jerky and inconsistent.
**
** Conversion:
** - tv_sec is already in seconds
** - tv_usec is in microseconds, so we divide by 1,000,000 to convert
** - Result: precise time as decimal seconds (e.g., 1732800123.456789)
**
** Used for: Frame-rate independent movement and rotation speeds
*/
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
