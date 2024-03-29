/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 23:42:09 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 16:01:09 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	change_dir(char *const *args, char *path, char *home)
{
	if (access(args[1], F_OK) == 0 && !is_dir(args[1]))
	{
		write(2, "minishell: cd: ", 15);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": Not a directory\n", 18);
		if (path)
			free(path);
		if (home)
			free(home);
		return (1);
	}
	else if (chdir(args[1]) == -1)
	{
		write (2, "minishell: cd: ", 15);
		write (2, args[1], ft_strlen(args[1]));
		write (2, ": No such file or directory\n", 28);
		if (path)
			free(path);
		if (home)
			free(home);
		return (1);
	}
	return (0);
}

/*****************************************************************************
 * Builtin function to change the current working directory.
 ****************************************************************************/

int	ft_cd(char **args, char *line)
{
	char	*path;
	char	*home;
	char	***env;

	(void) line;
	env = gc_env_alloc(-1);
	path = getcwd(NULL, 0);
	home = NULL;
	if (args[1] == NULL)
	{
		home = get_env("HOME", env);
		if (chdir(home) == -1)
			return (1);
	}
	else if (change_dir(args, path, home) == 1)
		return (1);
	if (home)
		free(home);
	free (path);
	path = getcwd(NULL, 0);
	if (set_env("PWD", path) == -1)
		return (1);
	free(path);
	return (0);
}

/*****************************************************************************
 * Builtin function to print arguments to the standard output.
 ****************************************************************************/

int	ft_echo(char **args, char *line)
{
	int	i;
	int	trailing_newline;

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

int	ft_pwd(char **args, char *line)
{
	char	*path;
	char	***env;

	(void) args;
	(void) line;
	env = gc_env_alloc(-1);
	path = get_env("PWD", env);
	printf("%s\n", path);
	free(path);
	return (0);
}

/*****************************************************************************
 * Builtin function to exit the shell.
 ****************************************************************************/

int	ft_exit(char **args, char *line)
{
	int	exit_status;

	(void)line;
	exit_status = 0;
	if (args[1])
		exit_status = ft_atoi(args[1]);
	gc_env_free();
	gc_free();
	exit(exit_status);
}
