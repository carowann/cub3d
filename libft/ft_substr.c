/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:37:26 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/12 18:29:33 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	subs = (char *)ft_calloc((len + 1), sizeof(char));
	if (!subs)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		subs[i] = s[start];
		start++;
		len--;
		i++;
	}
	return (subs);
}
// while (i < len)
// {
//     subs[i] = s[start + i];
//     i++;
// }
/* 
int main(void)
{
	// Test 1: Basic substring
	char *str1 = "Hello World";
	char *sub1 = ft_substr(str1, 6, 5);  // Should get "World"
	printf("Test 1: '%s'\n", sub1);
	free(sub1);

	// Test 2: Empty string
	char *str2 = "";
	char *sub2 = ft_substr(str2, 0, 5);  // Should get ""
	printf("Test 2: '%s'\n", sub2);
	free(sub2);

	// Test 3: Start beyond string length
	char *str3 = "Hello";
	char *sub3 = ft_substr(str3, 10, 2);  // Should get ""
	printf("Test 3: '%s'\n", sub3);
	free(sub3);

	// Test 4: Length longer than remaining string
	char *str4 = "Hello";
	char *sub4 = ft_substr(str4, 2, 10);  // Should get "llo"
	printf("Test 4: '%s'\n", sub4);
	free(sub4);

	// Test 5: Zero length
	char *str5 = "Hello";
	char *sub5 = ft_substr(str5, 1, 0);  // Should get ""
	printf("Test 5: '%s'\n", sub5);
	free(sub5);

	return (0);
} */