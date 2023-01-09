/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:18:44 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 18:16:42 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * Get all the path in current environment
 * @return an array with all the path
 *****************************************************************************/

char	**get_path(void)
{
	char	*env_path;
	char	**path_array;
	int		i;

	env_path = getenv("PATH");
	path_array = ft_split(env_path, ':');
	i = 0;
	while (path_array[i])
	{
		garbage_collector_add(path_array[i]);
		i++;
	}
	garbage_collector_add(path_array);
	return (path_array);
}

/******************************************************************************
 * return the path of the parent directory of *path
 * @param path directory from which we re looking parent
 * @return null terminated string of the parent path
 *****************************************************************************/

static char	*get_parent(char *path)
{
	char	*parent;

	parent = ft_strrchr(path, '/');
	if (parent)
	{
		*parent = '\0';
	}

	return (path);
}

/*****************************************************************************
 * look into the path environement variable for the path of the command name
 * @param name null terminated string of the name of the command
 * @param path array of string built from the environement variable
 * @return full_path or NULL if binary not found in path
 * 
 * [NORME]: HAVE TO FREE RESULT VAR
 * 
 ****************************************************************************/

static char	*return_path(DIR *dp, char *path_str, char *name)
{
	char	*tmp;
	char	*result;

	closedir(dp);
	tmp = ft_strjoin(path_str, "/");
	result = ft_strjoin(tmp, name);
	free(tmp);
	return (result);
}

char	*get_full_path(char *name, char **path)
{
	int				i;
	DIR				*dp;
	struct dirent	*entry;
	char			*tmp;

	i = 0;
	while (path[i] != 0)
	{
		dp = opendir(path[i]);
		if (dp != NULL)
		{
			entry = readdir(dp);
			while (entry)
			{
				if (ft_strncmp(name, entry->d_name, strlen(name) + 1) == 0)
					return (return_path(dp, path[i], name));
				entry = readdir(dp);
			}
		}
		closedir(dp);
		i ++;
	}
	return (NULL);
}

/******************************************************************************
 * if name start with "/" "../" or "./" it's an absolute or relative path
 * return the full path
 * @param name null terminated string of the name of the command
 * @return full path or NULL if not absolute or relative path
 * [NORME]: DELETED COMMENTED STRING "garbage_collector_add(parent);"
 * 			right before return string
 *****************************************************************************/

char	*check_absolute_relative_path(char *name)
{
	char	*parent;

	if (name[0] == '/')
		return (name);
	else if (name[0] == '.' && name[1] == '/')
		return (ft_strjoin(getcwd(NULL, 0), name + 1));
	else if (name[0] == '.' && name[1] == '.' && name[2] == '/')
	{
		parent = get_parent(getcwd(NULL, 0));
		return (ft_strjoin(parent, name + 2));
	}
	else
		return (NULL);
}
