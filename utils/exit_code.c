/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:44:11 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/17 01:46:12 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
/*****************************************************************************
 * Simple util who return the exit code passed as argv[1]
 ****************************************************************************/
int	main(int argc,char **argv)
{
	int	return_code;
	if (argc < 2 || argc > 2)
	{
		printf("Usage %s [EXITCODE]\nEXITCODE >=0 <=255\n",argv[0]);
		return (0);
	}
	return_code = atoi(argv[1]);
	if (return_code < 0 || return_code > 255)
		printf("EXITCODE should be between 0 and 255\n");
	return (return_code);
}