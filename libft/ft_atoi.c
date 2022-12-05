/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:33:11 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:13:36 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static char	*ft_remove_space(const char *str)
{
	size_t	pos;

	pos = 0;
	while ((str[pos] != '\0') && ((str[pos] == ' ')
			|| ((str[pos] >= 9) && (str[pos] <= 13))))
		pos ++;
	return ((char *)str + pos);
}

static long int	check_result(long int result, int signe)
{
	if (result > INT_MAX || result < INT_MIN)
	{
		if (signe < 1)
			return (0);
		else
			return (-1);
	}
	return (result);
}

int	ft_atoi(const char *nptr)
{
	int			signe;
	size_t		pos;
	long int	result;

	signe = 1;
	result = 0;
	nptr = ft_remove_space(nptr);
	if (nptr[0] == '-')
	{
		signe *= -1;
		nptr ++;
	}
	else if (nptr[0] == '+')
		nptr ++;
	pos = 0;
	while ((nptr[pos] != '\0') && (ft_isdigit(nptr[pos])))
	{
		result = result * 10 + nptr[pos] - '0';
		pos ++;
	}
	result *= signe;
	result = check_result(result, signe);
	return (result);
}
