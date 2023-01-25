/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 23:42:09 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/25 11:43:48 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/*****************************************************************************
 * Builtin function to change the current working directory.
 ****************************************************************************/

int	ft_cd(char **args, char ***env,char *line)
{
	char	*path;
	char	*home;

	(void) line;
	path = getcwd(NULL, 0);
	home = NULL;
	if (args[1] == NULL)
	{
		home = get_env("HOME", env);
		if (chdir(home) == -1)
			return (-1);
	}
	else if (chdir(args[1]) == -1)
	{
		return (-1);
	}
	if (home)
		free(home);
	free (path);
	path = getcwd(NULL, 0);
	if (set_env(env, "PWD", path) == -1)
		return (-2);
	free(path);
	return (0);
}

/*****************************************************************************
 * Builtin function to print arguments to the standard output.
 ****************************************************************************/

int	ft_echo(char **args, char ***env,char *line)
{
	int	i;
	int	trailing_newline;

	(void) env;
	(void) line;
	trailing_newline = 1;
	i = 1;
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
	{
		trailing_newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (trailing_newline == 1)
		printf("\n");
	return (0);
}

/*****************************************************************************
 * Builtin function to print the current working directory.
 ****************************************************************************/

int	ft_pwd(char **args, char ***env,char *line)
{
	char *path;

	(void) args;
	(void) line;
	path = get_env("PWD", env);
	printf("%s\n", path);
	free(path);
	return (0);
}

/*****************************************************************************
 * Builtin function to exit the shell.
 ****************************************************************************/

int	ft_exit(char **args, char ***env,char *line)
{
	(void) line;
	(void) args;
	free_env(env);
	gc_free();
	exit(EXIT_SUCCESS);
}