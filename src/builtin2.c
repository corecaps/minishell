/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:07:37 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/21 02:18:53 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * 
 * Need to test ft_export(), ft_env(), ft_unset()
 * 
 *****************************************************************************/

int	ft_env(char **args, char ***env)
{
	int	i;

	(void) args;
	i = 0;
	while ((*env)[i])
	{
		printf("%s\n", (*env)[i]);
		i++;
	}
	return (0);
}

int	ft_unset(char **args, char ***env)
{
	int		i;
	int		j;
	size_t	index;

	(void) args;
	(void) env;
	i = 1;
	while (args[i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (!ft_strncmp(args[i], (const char *)(*env)[j],
				ft_strlen(args[i])))
			{
				index = (size_t) j;
				realloc_environ(env, count_env(env) - 1, index);
				break ;
			}
			j++;
		}
		i++;
	}	
	return (0);
}
