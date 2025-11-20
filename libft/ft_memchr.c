/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:18:12 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/13 18:15:36 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	c = (unsigned char)c;
	if (n > 0)
	{
		while (i < n)
		{
			if (*ptr == c)
			{
				return (ptr);
			}
			ptr++;
			i++;
		}
	}
	return (NULL);
}

/* int main(void)
{
	const char str[] = "";
	char *result;
	
	//existing char
	result = ft_memchr(str, 'w', sizeof(str));
	if (result != NULL)
		printf("Character found: %c\n", *result);
	else
		printf("Character not found\n");
	//non existing char
	result = ft_memchr(str, 'z', sizeof(str));
	if (result != NULL)
		printf("Character found: %c\n", *result);
	else
		printf("Character not found\n");
	return 0;
} */