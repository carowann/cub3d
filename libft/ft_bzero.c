/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:43:04 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/04 17:19:07 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
	return (s);
}
/* 
int main()
{
    char str[50] = "Polpi fritti";
    printf("Original string: %s\n", str);

    // Set the 0
    ft_bzero(str, 5);
    printf("Modified string: %s\n", str);
    return 0;
} */