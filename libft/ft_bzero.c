/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:27:54 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 14:14:46 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	pos;
	char	*ptr_s;

	pos = 0;
	ptr_s = (char *) s;
	if (n == 0)
		return ;
	while (pos < n)
	{
		ptr_s[pos] = 0;
		pos ++;
	}
}
