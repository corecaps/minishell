/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:26:42 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/09 23:32:02 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		size;
	char	*dest;
	int		pos;

	pos = 0;
	size = ft_strlen (src);
	dest = malloc(sizeof(char) * (size + 1));
	if (dest != NULL)
	{
		while (*(src + pos) != '\0')
		{
			*(dest + pos) = *(src + pos);
			pos ++;
		}
		*(dest + pos) = '\0';
	}
	return (dest);
}
