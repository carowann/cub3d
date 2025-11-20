/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:14:06 by giomastr          #+#    #+#             */
/*   Updated: 2025/05/09 15:35:02 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format(char c, va_list args)
{
	int	print_len;

	print_len = 0;
	if (c == '%')
		print_len += ft_putchar_fd(c, 1);
	else if (c == 'c')
		print_len += ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		print_len += ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'p')
		print_len += ft_put_ptr(va_arg(args, uintptr_t));
	else if (c == 'd' || c == 'i')
		print_len += ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'u')
		print_len += ft_putnbr_base_fd(va_arg(args, unsigned int), BASE10, 1);
	else if (c == 'x')
		print_len += ft_putnbr_base_fd(va_arg(args, unsigned int), BASE16, 1);
	else if (c == 'X')
		print_len += ft_putnbr_base_fd(va_arg(args, unsigned int), BASE16UP, 1);
	return (print_len);
}

int	ft_printf(const char *form, ...)
{
	int			i;
	int			count;
	va_list		args;

	va_start (args, form);
	i = 0;
	count = 0;
	if (!form)
		return (-1);
	while (form[i] != '\0')
	{
		if (form[i] == '%' && form[i + 1])
			count += format(form[++i], args);
		else
			count += ft_putchar_fd(form[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}

/*
int main()
{
	char str[] = "virgola";
	char c  = 's';
	int	n = 1;
	int nb = 0;
	int xs = 42;
	int dub = 43;
	const char *ptr = "42";
	// generic test
	ft_printf("ciao %cono %s, %cono %d gattin%i\n", c, str, c, n, nb);
	printf("ciao %cono %s, %cono %d gattin%i\n", c, str, c, n, nb);

	ft_printf("%x l%uks better than %X\n", xs, dub, xs);
	printf("%x l%uks better than %X\n", xs, dub, xs);

	ft_printf("Hell's address is %p\n", ptr);
	printf("Hell's address is %p\n", ptr);

	// Limit cases
	ft_printf("Max int: %d\n", INT_MAX);
	printf("Max int: %d\n", INT_MAX);

	ft_printf("Min int: %d\n", INT_MIN);
	printf("Min int: %d\n", INT_MIN);

	ft_printf("Max unsigned int: %u\n", UINT_MAX);
	printf("Max unsigned int: %u\n", UINT_MAX);

	ft_printf("Null pointer: %p\n", NULL);
	printf("Null pointer: %p\n", NULL);

	ft_printf("Empty string: %s\n", "");
	printf("Empty string: %s\n", "");

	ft_printf("Percent sign: %%\n");
	printf("Percent sign: %%\n");


	// NULL and edge cases
	ft_printf(NULL);
   	printf(NULL); //skips it
    ft_printf("");
    printf(""); //SKIPS IT
	ft_printf("%s\n", NULL);
	printf("%s\n", NULL); //prints (NULL)
    ft_printf("%s\n", "");
	printf("%s\n", "");//prints empty space

    // Extreme numbers
    ft_printf("%d\n", INT_MIN); //OK
    ft_printf("%d\n", INT_MAX); //OK
    ft_printf("%x\n", UINT_MAX);//OK
    ft_printf("%X\n", UINT_MAX);//OK


    // Multiple % signs
    ft_printf("%%%%%%%%%%\n");
	printf("%%%%%%%%%%\n");

    // Zero values
    ft_printf("%d%x%X%p\n", 0, 0, 0, NULL);
	printf("%d%x%X%p\n", 0, 0, 0, NULL);
} */
