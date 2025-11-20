/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:18:46 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/13 18:17:10 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	c = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (s);
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}

/* int main()
{
    char str[50] = "Hello, World!";
    printf("Original string: %s\n", str);

    // Set the first 5 characters to 'A'
    ft_memset(str, 'A', 5);
    printf("Modified string: %s\n", str);

    // Set the entire string to 'B'
    ft_memset(str, 'B', sizeof(str));
    printf("Modified string: %s\n", str);

    return 0;
} */