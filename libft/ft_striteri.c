/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:22:57 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:19:45 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	pos;

	pos = 0;
	if (s && f)
	{
		while (s[pos])
		{
			f(pos, &s[pos]);
			pos ++;
		}
	}
}
