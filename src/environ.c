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
 * @return 1 if success, 0 if error
 *****************************************************************************/

int	realloc_environ(char ***env,size_t size)
{
	char	**new_env;
	size_t	i;

	if (env == NULL || *env == NULL || size == 0)
		return (0);
	new_env = malloc(sizeof(char *) * (size + 1));
	if (new_env == NULL)
		return (0);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = NULL;
	del_environ(env);
	*env = new_env;
	return (1);
}