/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:10:04 by giomastr          #+#    #+#             */
/*   Updated: 2025/01/21 16:34:20 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(unsigned int n, unsigned int base, int fd)
{
	char	digit;
	int		flag;
	int		printed;

	printed = 0;
	flag = 0;
	digit = 0;
	if (base == BASE16UP)
	{
		flag = 1;
		base--;
	}
	if (n >= base)
		printed += ft_putnbr_base_fd((n / base), base + flag, fd);
	if ((n % base) < 10)
		digit = (n % base) + 48;
	else
	{
		if (base + flag == BASE16)
			digit = (n % base) - 10 + 97;
		else if (base + flag == BASE16UP)
			digit = (n % base) - 10 + 65;
	}
	printed += ft_putchar_fd(digit, fd);
	return (printed);
}

/* if (base < 2 || base > 16)
		return (-1); */
/* 
int main(void)
{
	//int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int fd = 1;
	if (fd == -1)
	{
		return 1;
	}
	ft_putnbr_base_fd(255, BASE16UP, fd); // Should print "FF" in hexadecimal
	write(1, "\n", 1);
	ft_putnbr_base_fd(255, BASE16, fd); // Should print "ff" in hexadecimal
	write(1, "\n", 1);
	ft_putnbr_base_fd(255, BASE10, fd); // Should print "255" in decimal
	write(1, "\n", 1);
	ft_putnbr_base_fd(255, 2, fd);  // Should print "11111111" in binary
	write(1, "\n", 1);
	ft_putnbr_base_fd(255, 12, fd); // Should print "193" in base 12

	close(fd);
	return 0;
} */
