/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:10:05 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/17 10:50:31 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char **buble_sort(char **env, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) <= 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	print_sorted(char ***env_pointer)
{
	char	**env;
	char  **res;
	int   size;

	env = *env_pointer;
	size = 0;
	while (env[size])
		size++;
	env = buble_sort(env, size);
	size = 0;
	while (env[size])
	{
		printf("%s\n", env[size++]);
	}
}
