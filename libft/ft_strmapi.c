/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:24:47 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/16 12:43:12 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* char	unosiunono(unsigned int i, char c)
{
	if (i % 2 == 0)
		c -= 32;
	return (c);
} */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*mod;

	i = 0;
	len = ft_strlen(s);
	mod = (char *)ft_calloc(len + 1, sizeof(char));
	if (!mod)
		return (NULL);
	if (!s[i])
		return (mod);
	while (s[i])
	{
		mod[i] = (*f)(i, s[i]);
		i++;
	}
	return (mod);
}

/* int main()
{
    char s[] = "bombastic";
    char *result = ft_strmapi(s, unosiunono);
    printf("Test (original test):\n");
    printf("Input: %s\n", s);
    printf("Output: %s\n", result);
    free(result);
} */
