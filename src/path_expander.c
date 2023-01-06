/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:18:44 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/05 11:18:48 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * Get all the path in current environment
 * @return an array with all the path
 *****************************************************************************/

char	**get_path()
{
	char	*env_path;
	char	**path_array;

	env_path = getenv("PATH");
	path_array = ft_split(env_path,':');
	return (path_array);
}

/******************************************************************************
 * return the path of the parent directory of *path
 * @param path directory from which we re looking parent
 * @return null terminated string of the parent path
 *****************************************************************************/

char *get_parent(char *path)
{
	char *parent;

	parent = ft_strrchr(path,'/');
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
 ****************************************************************************/

char	*get_full_path(char *name,char **path)
{
	int				i;
	DIR				*dp;
	struct dirent	*entry;

	i = 0;
	while (path[i] != 0)
	{
		dp = opendir(path[i]);
		if (dp != NULL)
		{
			entry = readdir(dp);
			while (entry)
			{
				if (ft_strncmp(name,entry->d_name, strlen(name)+1) == 0) // TODO Refactor to prevent leak on the double join
					return (ft_strjoin(ft_strjoin(path[i],"/"),name));
				entry = readdir(dp);
			}
		}
		closedir(dp);
		i ++;
	}
	printf("heheh\n");
	return (NULL);
}

/******************************************************************************
 * if name start with "/" "../" or "./" it's an absolute or relative path
 * return the full path
 * @param name null terminated string of the name of the command
 * @return full path or NULL if not absolute or relative path
 *****************************************************************************/

char	*check_absolute_relative_path(char *name)
{
	if (name[0] == '/')
		return (name);
	else if (name[0] == '.' && name[1] == '/')
		return (ft_strjoin(getcwd(NULL,0),name+1));
	else if (name[0] == '.' && name[1] == '.' && name[2] == '/')
		return(ft_strjoin(get_parent(getcwd(NULL,0)),name+2));
	else
		return (NULL);
}

/******************************************************************************
 * Find the binary in the path
 * @return the full path of the binary
 * @param name null terminated string of the name of the command
 *****************************************************************************/

char	*find_binary(char *name)
{
	char	*final_path;
	char	**path;

	final_path = check_absolute_relative_path(name);
	if (final_path)
		return (final_path);
	path = get_path();
	final_path = get_full_path(name, path);
	if (final_path && access(final_path,X_OK) != -1)
		return (final_path);
	else
		return (NULL);
}