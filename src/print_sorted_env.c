/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:10:05 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/19 10:40:13 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**buble_sort(char **env, int size)
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

static char	**get_copy_of(char ***origin_env)
{
	char	**copy_env;
	int		env_size;
	int		i;

	i = 0;
	env_size = count_env(origin_env);
	copy_env = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!copy_env)
		copy_env = NULL;
	while (i < env_size)
	{
		copy_env[i] = ft_strdup((*origin_env)[i]);
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

void	free_env_copy(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	print_sorted(char ***env_pointer)
{
	char	**env;
	int		size;

	env = get_copy_of(env_pointer);
	size = 0;
	while (env[size])
		size++;
	env = buble_sort(env, size);
	size = 0;
	while (env[size])
	{
		printf("%s\n", env[size++]);
	}
	free_env_copy(env);
}
