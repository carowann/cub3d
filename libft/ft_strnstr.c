/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:04:45 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/04 18:54:39 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (little[j] == big[i + j] && big[i + j] && little[j])
			j++;
		if (little[j] == 0 && j + i <= len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/* 
int main()
{
	char big[] = "I like bubble tea bubble";
	char little[] = "bubble";
	printf("%s\n", ft_strnstr(big, little, 13));
	return 0;
} */