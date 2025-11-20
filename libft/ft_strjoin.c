/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:59:26 by giomastr          #+#    #+#             */
/*   Updated: 2025/05/09 15:36:40 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	tot_len;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	tot_len = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)ft_calloc(tot_len + 1, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i++] = s2[j++];
	}
	joined[i] = '\0';
	return (joined);
}
/*
int main()
{
	char s1[] = "bella ";
	char s2[] = "zi0";
	printf("%s\n", ft_strjoin(s1, s2));
	return 0;
} */
