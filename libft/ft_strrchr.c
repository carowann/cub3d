/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:19:52 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/16 12:38:02 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (c > 127)
		c = c % 128;
	while (len >= 0)
	{
		if ((char)c == *(s + len))
			return ((char *)(s + len));
		len--;
	}
	if (c == '\0')
		return ((char *)(s + len));
	return (NULL);
}
/* 
int main()
{
	char  s[] = "beluga";
	printf("%s\n", ft_strrchr(s, 'g'));
	printf("%s\n", strrchr(s, 'g'));

	printf("%s\n", ft_strrchr(s, 'l'));
	printf("%s\n", strrchr(s, 'l'));

	printf("%s\n", ft_strrchr(s, 'c'));
	printf("%s\n", strrchr(s, 'c'));
	return 0;
} */