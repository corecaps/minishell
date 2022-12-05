/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:32:49 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:19:35 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	size_t	pos;
	size_t	max;

	max = ft_strlen(src);
	pos = 0;
	while (pos < max)
	{
		if (src[pos] != (char) c)
			pos ++;
		else
			return ((char *)&src[pos]);
	}
	if (c == src[pos])
		return ((char *)&src[pos]);
	return (NULL);
}
