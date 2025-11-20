/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:24:13 by giomastr          #+#    #+#             */
/*   Updated: 2025/01/16 19:00:02 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		len = 1;
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
		len += ft_putnbr_fd((nb / 10), fd);
	len += ft_putchar_fd(((nb % 10) + 48), fd);
	return (len);
}

/* int main(void)
{
	int fd;

	// Open a file to write the output
	fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}

	// Test 1: Positive number
	// printf("Test 1: Writing positive number 12345 to file\n");
	// ft_putnbr_fd(12345, fd);

	// Test 2: Negative number
	printf("Test 2: Writing negative number -12345 to file\n");
	ft_putnbr_fd(-7878, fd);

	// Test 3: Zero
	// printf("Test 3: Writing zero to file\n");
	// ft_putnbr_fd(0, fd);

	// Test 4: Large number
	// printf("Test 4: Writing large number 2147483647 to file\n");
	// ft_putnbr_fd(2147483647, fd);

	// Close the file
	close(fd);

	printf("Check the output.txt file for results.\n");

	return (0);
} */