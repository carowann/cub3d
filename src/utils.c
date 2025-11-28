/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:35:52 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/28 15:32:24 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_error_message(char *msg)
{
	ft_printfd(STDERR_FILENO, "%s", msg);
}

double	get_current_time(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != SUCCESS)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_TIME_FAIL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}
