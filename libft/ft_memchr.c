/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:52:52 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:17:25 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*search;
	unsigned char	*found;
	size_t			pos;

	pos = 0;
	search = (unsigned char *) s;
	found = NULL;
	while (pos < n)
	{
		if ((unsigned char)search[pos] != (unsigned char) c)
			pos ++;
		else
		{
			found = search + pos;
			break ;
		}
	}
	return ((void *)found);
}
