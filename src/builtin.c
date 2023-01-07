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

int	ft_cd(char **args,char **env)
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
	if (set_env(&env,"PWD", getcwd(NULL,0)) == -1)
		return (-2);
	printf("PWD = %s",get_env("PWD",env));
	printf("cwd = %s",getcwd(NULL,0));
	free(path);
	return (0);
}

int	ft_echo(char **args,char **env)
{
	int	i;
	int trailing_newline;

	(void) env;
	trailing_newline = 0;
	i = 1;
	if (args[1] && !ft_strncmp(args[1],"-n",3))
	{
		trailing_newline = 1;
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

int	ft_pwd(char **args,char **env)
{
	(void) args;

	printf("%s\n", get_env("PWD", env));
	return (0);
}