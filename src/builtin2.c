/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:07:37 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/19 10:39:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * 
 * Need to test ft_export(), ft_env(), ft_unset()
 * 
 *****************************************************************************/

int	ft_env(char **args, char ***env)
{
	int	i;

	(void) args;
	i = 0;
	while ((*env)[i])
	{
		printf("%s\n", (*env)[i]);
		i++;
	}
	return (0);
}

/******************************************************************************
 * find index of '=' separator to split on key-value
 * @param str a string where to find '='
 * @return	j (index of '=') if success, 
 * 			-1 if there isn't '=' in the string
 * 			-2 if there is a var name error
 *****************************************************************************/

static int	get_stop(const char *str)
{
	int	j;
	int	stop;

	stop = -1;
	j = 0;
	while (str[j])
	{
		if (str[0] == '?' && str[1] == '=')
			return (1);
		else if (str[j] == '=' && j != 0)
			return (j);
		else if ((str[j] < 65 || (str[j] > 90
					&& str[j] < 97) || str[j] > 122) && stop == -1)
		{
			printf("export error: invalid symbols\n");
			return (-2);
		}
		j++;
	}
	return (-1);
}

static void	to_set_env(char ***env, char *arg, int stop)
{
	char	*key;
	char	*value;

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
	set_env(env, key, value);
	if (stop > -1)
	{
		free(key);
		free(value);
	}
}

int	ft_export(char **args, char ***env)
{
	int		i;
	int		stop;

	i = 1;
	if (args[i])
	{
		while (args[i])
		{
			stop = get_stop(args[i]);
			if (stop == -2)
				return (-100);
			to_set_env(env, args[i], stop);
			i++;
		}
	}
	else
		print_sorted(env);
	return (0);
}

int	ft_unset(char **args, char ***env)
{
	int		i;
	int		j;
	size_t	index;

	(void) args;
	(void) env;
	i = 1;
	while (args[i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (!ft_strncmp(args[i], (const char *)(*env)[j],
				ft_strlen(args[i])))
			{
				index = (size_t) j;
				realloc_environ(env, count_env(env) - 1, index);
				break ;
			}
			j++;
		}
		i++;
	}	
	return (0);
}
