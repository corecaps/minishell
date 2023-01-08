/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:11:08 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/06 01:11:49 by jgarcia          ###   ########.fr       */
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

	if(env == NULL || *env == NULL)
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

	if(env == NULL)
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
 * @param env Pointer to Environment
 * @param size New size of the environment array
 * @return 0 if success, -1 if error
 *****************************************************************************/

int	realloc_environ(char ***env,size_t size) //I guess we have leaks here
{
	char	**new_env;
	size_t	i;

	if (env == NULL || size == 0 || size <= count_env(env))
		return (-1);
	new_env = malloc(sizeof(char *) * (size + 1));
	if (new_env == NULL)
		return (-1);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = NULL;
//	del_environ(env);
	*env = new_env;
	return (0);
}
/******************************************************************************
 * Add a variable to the environment
 * @param env Pointer to Environment
 * @param name Name of the variable
 * @param value Value of the variable
 * @return 0 if success, -1 if error
 *****************************************************************************/

int	set_env(char ***env,char *key,char *value)
{
	size_t	i;
	size_t	size;
	char	*tmp;

	i=0;
	//FOR TESTING
	// printf("\tin set_env()\n");
	// printf("\tkey = %s\n\tvalue = %s\n", key, value);
	// int j = 0;
	// while (*env[j])
	// {
	// 	printf("%s\n", *env[j]);	
	// 	j++;
	// }
	// printf("\tbefore set_env() count = %d\n", j);
	//
	while ((*env)[i])
	{
		tmp = ft_strjoin(key,"=");
		if (ft_strncmp(tmp,(*env)[i],ft_strlen(tmp)) == 0)
			break;
		i ++;
	}
	size = count_env(env);
	if (i > size -1)
	{
		realloc_environ(env, size + 1);
		if (!(*env))
			return (-1);
		(*env)[size] = ft_strjoin(tmp,value);
	}
	else
	{
		free ((*env)[i]);
		(*env)[i] = ft_strjoin(tmp,value);
	}
	//FOR TESTING
	// j = 0;
	// while (env[j])
	// {
	// 	j++;	
	// }
	// printf("\tafter set_env() count = %d\n", j);
	//
	free(tmp);
	return (0);
}

char	*get_env(char *key,char ***env)
{
	size_t	i;
	char	*tmp;
	char	*ret;

	if (key == NULL || env == NULL)
		return (NULL);
	i = 0;
	while ((*env)[i])
	{
		tmp = ft_strjoin(key,"=");
		if (ft_strncmp(tmp,(*env)[i],ft_strlen(tmp)) == 0)
		{
			ret = ft_substr((*env)[i],ft_strlen(tmp),ft_strlen((*env)[i]));
			free(tmp);
			return (ret);
		}
		i ++;
		free(tmp);
	}
	return (NULL);
}