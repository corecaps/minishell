/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 23:42:09 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:13:59 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	ft_cd(char **args, char ***env)
{
	char	*path;
	char	*home;

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

int	ft_echo(char **args, char ***env)
{
	int	i;
	int	trailing_newline;

	(void) env;
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

int	ft_pwd(char **args, char ***env)
{
	(void) args;
	printf("%s\n", get_env("PWD", env));
	return (0);
}

int	ft_exit(char **args, char ***env)
{
	t_garbage	*gc;

	(void) args;
	(void) env;
	gc = garbage_collector_add(NULL);
	if (gc)
		garbage_collector_free(gc);
	del_environ(env);
	// LEAKS (still reachable):
	// - AST
	// - token list
	// - data struct from main
	// - exec data struct
	// - parsing stack
	exit(EXIT_SUCCESS);
}
