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
 * Find the binary in the path
 * @return the full path of the binary
 * @param name the name of the binary
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

char 	*find_binary(char *name)
{
	char			**path;
	struct dirent	*entry;
	DIR				*dp;
	int				i,result;
	char			*final_path;

	if (name[0] == '/')
		return (name);
	if (name[0] == '.' && name[1] == '/')
		return (ft_strjoin(getcwd(NULL,0),name+1));
	if (name[0] == '.' && name[1] == '.' && name[2] == '/')
		return(ft_strjoin(get_parent(getcwd(NULL,0)),name+2));
	// TODO: add support for  ../
	// TODO : add support for builtins (cd, echo, exit, export, pwd, unset, env, exit)
	i = 0;
	path = get_path();
	while (path[i] != 0)
	{
		dp = opendir(path[i]);
		if (dp != NULL)
		{
			entry = readdir(dp);
			while (entry)
			{
				result = ft_strncmp(name,entry->d_name, strlen(name)+1);
				if (result == 0) { // TODO Refactor to prevent leak on the double join
					final_path =ft_strjoin(ft_strjoin(path[i],"/"),name);
					if (access(final_path,X_OK) != -1)
						return (final_path);
					else
						return (NULL);
				}
				entry = readdir(dp);
			}
		}
		closedir(dp);
		i ++;
	}
	return (NULL);
}