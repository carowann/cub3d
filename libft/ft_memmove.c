/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:18:09 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/16 12:59:50 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ds;
	unsigned char	*sr;

	if (!dest && !src)
		return (NULL);
	ds = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (ds < sr)
	{
		i = -1;
		while (++i < n)
			ds[i] = sr[i];
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			ds[i] = sr[i];
		}
	}
	return (dest);
}
/* 
int main() {
    char str[] = "abcdef";
    
    // Case 1: No overlap, forward copy
    printf("%s\n", ft_memmove(((void*)0), str, 4));
	printf("%s\n", memmove(((void*)0), str, 4));
    printf("Expected: 'ababcd' ") 

    // Case 2: Overlap, backward copy
    char str2[] = "abcdef";
    ft_memmove(str2, str2 + 2, 4);
    printf("%s\n", str2); // Expected: "cdefef"

    // Case 3: src == dest
    char str3[] = "abcdef";
    ft_memmove(str3, str3, 6);
    printf("%s\n", str3); // Expected: "abcdef"

    // Case 4: n == 0
    char str4[] = "abcdef";
    ft_memmove(str4 + 2, str4, 0);
    printf("%s\n", str4); // Expected: "abcdef"

    return 0;
} */