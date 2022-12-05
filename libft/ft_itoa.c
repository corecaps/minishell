/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:05:29 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:16:07 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_int_dec_size(long int n)
{
	int	size;

	size = 1;
	while (n > 9)
	{
		n /= 10;
		size ++;
	}
	return (size);
}

static void	ft_dectoascii(long int n, char *buf, size_t index)
{
	if (n > 9)
		ft_dectoascii(n / 10, buf, index - 1);
	buf[index] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	long long int	abs_n;
	char			*result;
	size_t			size;

	size = 0;
	abs_n = (long) n;
	if (n < 0)
	{
		abs_n *= -1;
		size ++;
	}
	size += ft_int_dec_size(abs_n);
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	ft_dectoascii(abs_n, result, size - 1);
	if (n < 0)
		result[0] = '-';
	result[size] = '\0';
	return (result);
}
