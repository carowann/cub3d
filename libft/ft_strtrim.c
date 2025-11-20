/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:00:32 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/09 17:15:53 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trimmed;
	size_t	size;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	size = end - start;
	trimmed = (char *)malloc(sizeof(char) * (size + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (i < size)
		trimmed[i++] = s1[start++];
	trimmed[i] = '\0';
	return (trimmed);
}
/* int main(void)
{
	// Test 1: Basic trim of single char
	printf("Test 1:\n");
	char *result1 = ft_strtrim("   Hello World   ", " ");
	printf("Input: '   Hello World   '\n");
	printf("Output: '%s'\n\n", result1);
	free(result1);

	// Test 2: Multiple chars to trim
	printf("Test 2:\n");
	char *result2 = ft_strtrim("...Hello..World...", ".");
	printf("Input: '...Hello..World...'\n");
	printf("Output: '%s'\n\n", result2);
	free(result2);

	// Test 3: Nothing to trim
	printf("Test 3:\n");
	char *result3 = ft_strtrim("Hello", " ");
	printf("Input: 'Hello'\n");
	printf("Output: '%s'\n\n", result3);
	free(result3);

	// Test 4: Empty string
	printf("Test 4:\n");
	char *result4 = ft_strtrim("", "123");
	printf("Input: ''\n");
	printf("Output: '%s'\n\n", result4);
	free(result4);

	// Test 5: Your original test case
	printf("Test 5:\n");
	char *result5 = ft_strtrim("olletto", "o");
	printf("Input: 'olletto'\n");
	printf("Expected: 'llett'\n");
	printf("Output: '%s'\n\n", result5);
	free(result5);

	return (0);
} */