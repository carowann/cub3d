/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:37:25 by giomastr          #+#    #+#             */
/*   Updated: 2025/01/23 16:39:02 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_ptr(uintptr_t ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		count += ft_putstr_fd("(nil)", 1);
	if (ptr)
	{
		count += ft_putstr_fd("0x", 1);
		count += ft_putnbr_base_fd(ptr, BASE16, 1);
	}
	return (count);
}
