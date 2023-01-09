/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:11:08 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 12:50:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * Count the variables in environment
 * @param env Pointer to Environment
 * @return Number of variables in environment
 *****************************************************************************/

size_t	count_env(char ***env)
{
	size_t	i;

	if (env == NULL || *env == NULL)
		return (0);
	i = 0;
	while ((*env)[i])
		i++;
	return (i);
}

/******************************************************************************
 * Delete the environment array and all the variables
 * @param env Pointer to Environment
 *****************************************************************************/

void	del_environ(char ***env)
{
	size_t	i;

	if (*env == NULL)
		return ;
	i = 0;
	while ((*env)[i])
	{
		free((*env)[i]);
		i++;
	}
	free(*env);
	*env = NULL;
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

int	realloc_environ(char ***env, size_t size, size_t index)
{
	char	**new_env;
	size_t	i;
	size_t	j;

	if (env == NULL || size == 0)
		return (-1);
	new_env = malloc(sizeof(char *) * (size + 1));
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
	new_env[i] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

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
