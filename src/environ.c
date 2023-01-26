/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:11:08 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/18 14:13:48 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * Count the variables in environment
 * @param env Pointer to Environment
 * @return Number of variables in environment
 *****************************************************************************/

int	count_env(char ***env)
{
	int	i;

	if (env == NULL || *env == NULL)
		return (0);
	i = 0;
	while ((*env)[i])
		i++;
	return (i);
}

/******************************************************************************
 * Reallocate the environment array to size size
 * [UPDATE]:Recode realloc func to decrease size of env. Index is the env[index]
 * 			element to unset. If we add element, index is -1. (also i deleted
 * 			size <= count_env(dev) condition in the first if statement) 
 * @param env Pointer to Environment
 * @param size New size of the environment array
 * @param index Index of element needs to unset
 * @return 0 if success, -1 if error
 *****************************************************************************/

int realloc_environ(size_t size, size_t index)
{
	char	**new_env;
	char 	***env;
	size_t	i;
	size_t	j;

	env = gc_env_alloc(-1);
	if (env == NULL || size == 0)
		return (-1);
	new_env = ft_calloc((size + 1), sizeof(char *));
	if (new_env == NULL)
		return (-1);
	i = 0;
	j = 0;
	while (j < size && (*env)[i])
	{
		if (index == i)
			i++;
		new_env[j] = ft_strdup((*env)[i]);
		i++;
		j++;
	}
	gc_env_free();
	(*env) = new_env;
	(*env)[j] = NULL;
	gc_env_add(*env);
	i = 0;
	while ((*env)[i])
	{
		gc_env_add((*env)[i]);
		i++;
	}
	return (0);
}

/*****************************************************************************
 * get the value of the environment variable key
 * @param key key of the environment variable
 * @param env pointer to the environment
 * @return NULL terminated string with the value of the environment variable
 ****************************************************************************/

char	*get_env(char *key, char ***env)
{
	size_t	i;
	char	*tmp;
	char	*ret;

	if (key == NULL || env == NULL)
		return (NULL);
	i = 0;
	while ((*env)[i])
	{
		tmp = ft_strjoin(key, "=");
		if (ft_strncmp(tmp, (*env)[i], ft_strlen(tmp)) == 0)
		{
			ret = ft_substr((*env)[i], ft_strlen(tmp), ft_strlen((*env)[i]));
			free(tmp);
			return (ret);
		}
		i ++;
		free(tmp);
	}
	return (NULL);
}