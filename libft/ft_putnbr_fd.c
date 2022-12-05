/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:15:36 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/17 09:24:01 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char		letter;
	long int	nombre;

	nombre = n;
	if (nombre < 0)
	{
		letter = '-';
		write(fd, &letter, 1);
		nombre = -nombre;
	}
	if ((nombre >= 0) && (nombre < 10))
	{
		letter = nombre + '0';
		write(fd, &letter, 1);
	}
	else
	{
		ft_putnbr_fd (nombre / 10, fd);
		ft_putnbr_fd (nombre % 10, fd);
	}
}
