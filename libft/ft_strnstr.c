/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:10:47 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:21:16 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	pos;
	size_t	s_pos;

	pos = 0;
	if (little[0] == '\0' || little == NULL)
		return ((char *)big);
	while ((big[pos] != '\0') && (pos < len))
	{
		s_pos = 0;
		while ((little[s_pos] == big[pos + s_pos]) && (pos + s_pos < len))
		{
			if (little[s_pos + 1] == '\0')
				return ((char *)big + pos);
			s_pos ++;
		}
		if (little[s_pos] == '\0')
			return ((char *)big + pos);
		pos ++;
	}
	return (NULL);
}
