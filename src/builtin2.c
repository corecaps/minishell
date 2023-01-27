/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:07:37 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 15:06:19 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * 
 *  print every environment variable
 * 
 *****************************************************************************/

int	ft_env(char **args, char *line)
{
	int		i;
	char	***env;

	(void) line;
	(void) args;
	env = gc_env_alloc(-1);
	i = 0;
	while ((*env)[i])
	{
		printf("%s\n", (*env)[i]);
		i++;
	}
	return (0);
}

/*****************************************************************************
 * Builtin function to unset an environment variable
 ****************************************************************************/

int	ft_unset(char **args, char *line)
{
	int		i;
	int		j;
	size_t	index;
	char	***envp;

	(void) line;
	(void) args;
	i = 1;
	envp = gc_env_alloc(-1);
	while (args[i])
	{
		j = 0;
		while ((*envp) && (*envp)[j])
		{
			if (!ft_strncmp(args[i], (const char *)(*envp)[j],
				ft_strlen(args[i])))
			{
				index = (size_t) j;
				realloc_environ(count_env(envp) - 1, index);
				break ;
				envp = gc_env_alloc(-1);
			}
			j++;
		}
		i++;
	}	
	return (0);
}
