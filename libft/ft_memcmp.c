/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:12:54 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:18:00 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			pos;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	pos = 0;
	while (pos < n)
	{
		if (str1[pos] == str2[pos])
			pos ++;
		else
			return (str1[pos] - str2[pos]);
	}
	return (0);
}
