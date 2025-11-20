/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:36:23 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/13 18:19:11 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/* 
int main()
{
	char src[10] = "calippo";
	char dst[10] = "brucali";
	ft_strlcpy(dst, src, 5);
	printf("%s\n", dst);
	printf("%zu\n", (ft_strlcpy(dst, src, 5)));

	//strlcpy(dst, src, 5);
	return 0;
} */