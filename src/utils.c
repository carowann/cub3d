/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:35:52 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/27 12:36:06 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	get_current_time(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != SUCCESS)
		cleanup_and_exit(data, EXIT_FAILURE, MSG_TIME_FAIL);
	return (tv.tv_sec);
}
