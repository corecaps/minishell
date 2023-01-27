/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:18:31 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 18:03:25 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "export.h"

/******************************************************************************
 * find index of '=' separator to split on key-value
 * @param str a string where to find '='
 * @return	j (index of '=') if success,
 * 			-1 if there isn't '=' in the string
 * 			-2 if there is a var name error
 *****************************************************************************/

static void	to_set_env(char ***env, char *arg, int stop)
{
	char	*key;
	char	*value;

	(void)env;
	if (stop > -1)
	{
		key = ft_substr(arg, 0, stop);
		value = ft_substr(arg, stop + 1, ft_strlen(arg) - stop);
	}
	else
	{
		key = arg;
		value = "";
	}
	set_env(key, value);
	if (stop > -1)
	{
		free(key);
		free(value);
	}
}

static int	check_params(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?')
		if (str[1] == '=')
			if (str[2] == '\0')
				return (1);
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '=')
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		else if (str[i] <= 47 || (str[i] >= 58 && str[i] <= 64)
			|| (str[i] >= 91 && str[i] <= 96) || str[i] >= 123)
			return (0);
		else if (str[i + 1] == '\0')
			return (i + 1);
		++i;
	}
	return (0);
}

static void	free_params(char **params)
{
	int	i;

	i = 0;
	while (params[i])
	{
		free(params[i]);
		params[i] = NULL;
		++i;
	}
	free(params);
	params = NULL;
}

int	ft_export(char **args, char *line)
{
	int		i;
	int		stop;
	char	**params;
	char	***env;

	(void) args;
	env = gc_env_alloc(-1);
	params = get_params(line, env, 0, 0);
	i = 1;
	if (params[i])
	{
		while (params[i])
		{
			stop = check_params(params[i]);
			if (stop)
				to_set_env(env, params[i], stop);
			else
				printf("invalid argument: %s\n", params[i]);
			i++;
		}
	}
	else
		print_sorted(env);
	free_params(params);
	return (0);
}
