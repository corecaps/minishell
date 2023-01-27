/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:20:07 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 15:05:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
 * copy environment array into a new array
 * @param env original environment array
 * @return a freshly allocated array of environment variables
 *****************************************************************************/

int	create_env(char **env, int argc, char **argv)
{
	char	***new_env;
	int		i;
	int		size;

	(void) argc;
	(void) argv;
//	new_env = (char **)ft_calloc((count_env(&env) + 1), sizeof(char *));
	size = count_env(&env) + 1;
	new_env = gc_env_alloc(size);
	if (new_env == NULL)
		return (0);
	i = 0;
	while (i < size - 1)
	{
		(*new_env)[i] = ft_strdup(env[i]);
		gc_env_add((*new_env)[i]);
		i++;
	}
	(*new_env)[i] = NULL;
	return (1);
}

/******************************************************************************
 * free memory allocated for environment array
 *****************************************************************************/

void	free_env(char ***env)
{
	int		i;
	char	**tmp_env;

	i = 0;
	tmp_env = *env;
	while (*(tmp_env + i))
	{
		free(*(tmp_env + i));
		*(tmp_env + i) = NULL;
		i++;
	}
	free(tmp_env);
}
