/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:12:39 by giomastr          #+#    #+#             */
/*   Updated: 2025/05/09 15:35:39 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*gnl_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	size_t			total_size;
	void			*alloc;
	unsigned char	*ptr;

	if (nmemb && size && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	alloc = malloc(total_size);
	if (!alloc)
		return (NULL);
	ptr = (unsigned char *)alloc;
	i = 0;
	while (i < total_size)
		ptr[i++] = 0;
	return (alloc);
}

char	*gnl_str_add(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*added;

	added = (char *)gnl_calloc(gnl_strlen(s1) + gnl_strlen
			(s2) + 1, sizeof(char));
	if (!added)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		added[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		added[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	return (added);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;

	if ((start + len) > gnl_strlen(s))
		len = gnl_strlen(s) - start;
	subs = (char *)gnl_calloc((len + 1), sizeof(char));
	if (!subs)
		return (NULL);
	i = 0;
	while (s && len > 0)
	{
		subs[i] = s[start];
		start++;
		len--;
		i++;
	}
	return (subs);
}

char	*gnl_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
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
