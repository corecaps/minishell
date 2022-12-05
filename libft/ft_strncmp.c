/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 01:26:42 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:21:06 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			pos;
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	pos = 0;
	if (n == 0)
		return (0);
	while ((pos < n - 1) && (s1[pos] != '\0'))
	{
		if (ps1[pos] == ps2[pos])
			pos ++;
		else
			break ;
	}
	return (ps1[pos] - ps2[pos]);
}
