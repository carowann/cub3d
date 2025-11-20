/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:17:02 by giomastr          #+#    #+#             */
/*   Updated: 2025/01/23 16:38:27 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
	{
		if (!s1 && !s2)
			return (0);
		if (!s1)
			return (-1);
		return (1);
	}
	i = 0;
	while (i < n && (s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int main(void)
// {
// 	char s1[] = "pitck";
// 	char s2[] = "pitch";
// 	//ft_strncmp(s1, s2, 5);
// 	printf("%d\n", (ft_strncmp(s1, s2, 3)));
// 	printf("%d\n", (strncmp(s1, s2, 3)));
// }