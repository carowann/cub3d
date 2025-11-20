/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:41:28 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/16 12:47:54 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (n == 0 || (!dest && !src))
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/* 
int main()
{
    char src[50] = "Hello, World!";
    char dest[50];

    printf("Source string: %s\n", src);

    // Copy the source string to the destination string
    ft_memcpy(dest, src, strlen(src) + 1); // +1 to include the null terminator
    printf("Destination string after memcpy: %s\n", dest);

    // Copy part of the source string to the destination string
    ft_memcpy(dest, src, 5);
    dest[5] = '\0'; // Null-terminate the string
    printf("Destination string after copying 5 characters: %s\n", dest);

    return 0;
} */