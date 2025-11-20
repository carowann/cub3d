/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:45:39 by giomastr          #+#    #+#             */
/*   Updated: 2025/05/06 17:43:39 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	delim(const char *s, char lim)
{
	if (*s == lim || *s == '\0')
		return (1);
	return (0);
}

static size_t	str_numb(const char *s, char lim)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (*s)
	{
		while (*s && delim(s, lim) == 1)
			s++;
		if (*s && delim(s, lim) == 0)
		{
			count++;
			while (*s && delim(s, lim) == 0)
				s++;
		}
	}
	return (count);
}

static char	*allocate_str(const char *str, char lim)
{
	char	*word;
	int		start;
	size_t	len;

	start = 0;
	len = 0;
	while (str[start] && delim(&str[start], lim) == 1)
		start++;
	while (str[start + len] && delim(&str[start + len], lim) == 0)
		len++;
	word = ft_substr(str, start, len);
	return (word);
}

static void	frii(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char lim)
{
	int		i;
	char	**split_matrix;

	split_matrix = (char **)ft_calloc(str_numb(s, lim) + 1, sizeof(char *));
	if (!split_matrix)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && delim(s, lim) == 1)
			s++;
		if (*s && delim(s, lim) == 0)
		{
			split_matrix[i] = allocate_str(s, lim);
			if (!split_matrix[i])
			{
				frii((char **)s);
				return (NULL);
			}
			i++;
			while (*s && delim(s, lim) == 0)
				s++;
		}
	}
	return (split_matrix);
}
/*

int main(void)
{
    // Test 1: Basic split
    char **str1 = ft_split("What you doin", ' ');
    printf("Space Test:\n");

	int i = 0;
	while (str1[i] != NULL)
	{
		printf("%s\n", str1[i]);
        free(str1[i]);
		i++;
	}
	free(str1);

	// Test 2: Multiple delimiters
	char **str2 = ft_split("hello,hello,baby,i,can't,hear,a,thing", ',');
    printf("Char Test:\n");

	i = 0;
	while (str2[i] != NULL)
	{
		printf("%s\n", str2[i]);
        free(str2[i]);
		i++;
	}
	free(str2);

    // Test 3: No delimiters
    char **str3 = ft_split("abracadabra", ' ');
    printf("No Lim Test:\n");
	i = 0;
	while (str3[i] != NULL)
	{
		printf("%s\n", str3[i]);
        free(str3[i]);
		i++;
	}
	free(str3);

    // Test 4: All delimiters
    char **str4 = ft_split("", ',');
    printf("Empty str Test 4:\n");
	i = 0;
	while (str4[i] != NULL)
	{
		printf("%s\n", str4[i]);
        free(str4[i]);
		i++;
	}
	free(str4);

    return 0;
} */