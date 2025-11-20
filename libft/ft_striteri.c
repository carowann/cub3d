/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:51:24 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/10 15:17:13 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* 
void	unosiunono(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c -= 32;
} */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* 
int main()
{
    char s[] = "bombastic";

    printf("Input: %s\n", s);
	ft_striteri(s, unosiunono);
    printf("Output: %s\n", s);
} */