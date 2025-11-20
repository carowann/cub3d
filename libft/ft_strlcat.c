/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:21:51 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/13 21:24:54 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	if (size <= dstlen)
		return (size + srclen);
	i = 0;
	while (dstlen + i < size - 1 && src[i] != '\0')
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen + i < size)
		dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
/* 
void test_strlcat(char *dst, const char *src, size_t size) {
    char buffer[100];
    strcpy(buffer, dst);
    size_t result = ft_strlcat(buffer, src, size);
    printf("dst=\"%s\", src=\"%s\", size=%zu -> result=%zu, 
	buffer=\"%s\"\n", dst, src, size, result, buffer);
}
int main() {
    // Test cases
    test_strlcat("Hello", " World", 0);
    test_strlcat("Hello", " World", 5);
    test_strlcat("Hello", " World", 10);
    test_strlcat("Hello", " World", 15);
    test_strlcat("", "World", 5);
    test_strlcat("Hello", "", 10);
    test_strlcat("", "", 5);
    test_strlcat("Hello", " World", 11);

    return 0;
} */