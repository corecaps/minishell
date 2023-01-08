/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 23:42:09 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/06 23:42:35 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	ft_cd(char **args,char ***env)
{
	char	*path;

	path = getcwd(NULL,0);
	if (!path)
		return (-1);
	if (args[1] == NULL)
	{
		if (chdir(get_env("HOME",env)) == -1)
			return (-1);
	}
	else if (chdir(args[1]) == -1)
	{
		return (-1);
	}
	if (set_env(env,"PWD", getcwd(NULL,0)) == -1)
		return (-2);
	free(path);
	return (0);
}

int	ft_echo(char **args,char ***env)
{
	int	i;
	int trailing_newline;

	(void) env;
	trailing_newline = 1;
	i = 0;
	if (args[1] && !ft_strncmp(args[1],"-n",3))
	{
		trailing_newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s",args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (trailing_newline == 1)
		printf("\n");
	return (0);
}

int	ft_pwd(char **args,char ***env)
{
	(void) args;

	printf("%s\n", get_env("PWD", env));
	return (0);
}

int ft_exit(char **args,char ***env)
{
	(void) args;
	(void) env;
	t_garbage *gc;

	gc = garbage_collector_add(NULL);
	garbage_collector_free(gc);
//	del_environ(env);
	exit(EXIT_SUCCESS);
	return (0);
}

/******************************************************************************
 * 
 * Need to test ft_export(), ft_env(), ft_unset()
 * 
 *****************************************************************************/

int	ft_env(char **args,char ***env)
{
	(void) args;
	//FOR TESTING EXPORT
	printf("In ft_env:\n\tenv address = [%p]\n", env);
	int i = 0;
	while((*env)[i])
	{
		printf("%s\n", (*env)[i]);
		i++;
	}
	printf("Env count = %d\n", i);
	//
	return (0);
}

int	ft_export(char **args, char ***env)
{
	char	*key;
	char	*value;
	int		i;
	int		j;
	int		stop;

	i = 1;
	while (args[i])
	{
		stop = -1;
		j = 0;
		while(args[i][j])
		{
			if (args[i][0] == '?')
			{
				stop = 1;
				break ;
			}
			else if (args[i][j] == '=' && j != 0)
			{
				stop = j;
				break ;
			}
			else if ((args[i][j] < 65 || (args[i][j] > 90 && args[i][j] < 97) //invalid symbols on input
				|| args[i][j] > 122) && stop == -1 )
			{
				printf("export error: invalid symbols []");
					return (-100); 	// maybe we need to skip this arg to continue with "continue ;"
			}
			j++;
		}
		if (stop > -1) //if we found '=' symbol in args
		{
			key = ft_substr(args[i], 0, stop);
			value = ft_substr(args[i], stop + 1, ft_strlen(args[i]) - stop);
		}
		else
		{
			key = args[i];
			value = "";
		}

		// printf("key = [%s]\nvalue = [%s]\n", key, value);
		set_env(env, key, value);
		i++;
	}
	// ft_env(NULL, env);
	return (0);
}



int	ft_unset(char **args, char ***env)
{
	int	i;
	int j;
	int index;

	(void) args;
	(void) env;
	i = 1;	
	while (args[i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (ft_strncmp(args[i], (*env)[i], ft_strlen(args[i])))
			{
				index = j;
				realloc_environ(env, count_env(env), index);
				break ;
			}
			j++;
		}
		i++;
	}	
	return (0);
}