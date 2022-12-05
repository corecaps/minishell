/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:51:34 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/25 14:55:43 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r_ptr;

	if ((size == 0) || (nmemb == 0))
		return (malloc(0));
	if ((size >= SIZE_MAX / nmemb) || (nmemb >= SIZE_MAX / size))
		return (NULL);
	r_ptr = malloc(size * nmemb);
	if (r_ptr == NULL)
		return (NULL);
	ft_memset(r_ptr, 0, nmemb * size);
	return ((char *)r_ptr);
}
