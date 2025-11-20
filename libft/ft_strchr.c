/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:05:46 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/16 13:03:55 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (c > 127)
		c = c % 128;
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
/* 
int main()
{
	char s[] = "diolupetto";

	printf("%s\n", ft_strchr(s, 1024));
	printf("%s\n", strchr(s, 1024));
	//printf("%s\n", ft_strchr(s, 'l'));
	//printf("%s\n", strchr(s, 'l'));
	//printf("%s\n", ft_strchr(s, 'a'));
	//printf("%s\n", strchr(s, 'a'));
	return 0;
} */
