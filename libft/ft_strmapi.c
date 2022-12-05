/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:42:30 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/18 23:51:47 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	pos;
	char	*result;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s) + 1;
	result = malloc(sizeof(char) * len);
	if (result == NULL)
		return (NULL);
	pos = 0;
	while (s[pos] != '\0')
	{
		result[pos] = f(pos, s[pos]);
		pos ++;
	}
	result[pos] = '\0';
	return (result);
}
