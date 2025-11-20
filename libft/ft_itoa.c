/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giomastr <giomastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:11:29 by giomastr          #+#    #+#             */
/*   Updated: 2024/12/13 18:23:05 by giomastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	n_len(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		nlen;
	long	nb;
	char	*result;

	nb = n;
	nlen = n_len(n);
	result = (char *)ft_calloc ((nlen + 1), sizeof(char));
	if (!result)
		return (NULL);
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	while (nlen > 0)
	{
		if (result[nlen - 1] == '-')
			break ;
		result[nlen - 1] = (nb % 10) + 48;
		nb = nb / 10;
		nlen--;
	}
	return (result);
}
/* 
int main()
{
	// int n = 776;
	// //printf("%i\n", n_len(n));
	// printf("%s\n", ft_itoa(n));

	// Test 1: Positive number
    int n1 = 12345;
    char *result1 = ft_itoa(n1);
    printf("Test 1: Positive number\n");
    printf("Input: %d\n", n1);
    printf("Output: %s\n\n", result1);
    free(result1);

	    // Test 2: Negative number
    int n2 = -12345;
    char *result2 = ft_itoa(n2);
    printf("Test 2: Negative number\n");
    printf("Input: %d\n", n2);
    printf("Output: %s\n\n", result2);
    free(result2);

    // Test 3: Zero
    int n3 = 0;
    char *result3 = ft_itoa(n3);
    printf("Test 3: Zero\n");
    printf("Input: %d\n", n3);
    printf("Output: %s\n\n", result3);
    free(result3);

    // Test 4: Large number
    int n4 = 2147483647;
    char *result4 = ft_itoa(n4);
    printf("Test 4: Large number\n");
    printf("Input: %d\n", n4);
    printf("Output: %s\n\n", result4);
    free(result4);

    // Test 5: Minimum integer value
    int n5 = INT_MIN;
    char *result5 = ft_itoa(n5);
    printf("Test 5: Minimum integer value\n");
    printf("Input: %d\n", n5);
    printf("Output: %s\n\n", result5);
    free(result5);

    return 0;
} */