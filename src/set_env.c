/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:51:03 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/09 13:17:15 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	empty_env(char ***env, char *key, char *value)
{
	char	*tmp;

	(*env) = malloc(sizeof(char *) * 2);
	if ((*env) == NULL)
		return (-1);
	tmp = ft_strjoin(key, "=");
	(*env)[0] = ft_strjoin(tmp, value);
	(*env)[1] = NULL;
	free(tmp);
	return (0);
}

static int	update_env(char ***env, size_t size, char *tmp, char *value)
{
	realloc_environ(env, size + 1, -1);
	if (!(*env))
		return (-1);
	(*env)[size] = ft_strjoin(tmp, value);
	return (0);
}

static int	find_var_index(char ***env, char *tmp)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(tmp, (*env)[i], ft_strlen(tmp)) == 0)
			break ;
		i ++;
	}
	return (i);
}

/******************************************************************************
 * Add a variable to the environment
 * @param env Pointer to Environment
 * @param name Name of the variable
 * @param value Value of the variable
 * @return 0 if success, -1 if error
 *****************************************************************************/

int	set_env(char ***env, char *key, char *value)
{
	size_t	i;
	size_t	size;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (tmp == NULL)
		return (-1);
	if ((*env) == NULL)
		return (empty_env(env, key, value));
	i = find_var_index(env, tmp);
	size = count_env(env);
	if (i > size -1)
		update_env(env, size, tmp, value);
	else
	{
		if ((*env)[i])
			free((*env)[i]);
		(*env)[i] = ft_strjoin(tmp, value);
	}
	free(tmp);
	return (0);
}
