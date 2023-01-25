/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:18:31 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/25 21:41:22 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*****************************************************************************
 * Get index to split string on key, value
 ****************************************************************************/

static int	get_stop(const char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[0] == '?' && str[1] == '=')
			return (1);
		else if (str[j] == '=' && j != 0)
			return (j);
		else if (str[j] < 48
			|| (str[j] >= '0' && str[j] <= '9' && j == 0)
			|| (str[j] > '9' && str[j] < 'A')
			|| (str[j] > 'Z' && str[j] < 'a')
			|| (str[j] > 'z'))
			return (-2);
		else if (str[j + 1] == '\0' && str[j] == '=')
			return (j);
		else if (str[j + 1] == '\0' && str[j] != '=')
			return (j + 1);
		j++;
	}
	return (-1);
}

/*****************************************************************************
 * Check arguments passed in ft_export
 ****************************************************************************/

static int	check_args(char **args)
{
	int		i;
	int		j;
	char	tmp;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '=' && args[i][1] != '\0')
			return (1);
		while (args[i][j] != '=' && args[i][j] != '\0')
		{
			tmp = args[i][j];
			if (tmp == '?' || tmp == '*'
				|| tmp == '!' || tmp == '&')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// int	ft_export(char **args, char ***env, char *line)
// {
// 	int		i;
// 	int		stop;

// 	i = 1;
// 	printf("\n%s\n", line);
// 	if (args[i])
// 	{
// 		if (check_args(args))
// 		{
// 			write(2, "Really bad args prevent to write others\n", 40);
// 			return (0);
// 		}
// 		while (args[i])
// 		{
// 			stop = get_stop(args[i]);
// 			if (stop != -2)
// 				to_set_env(env, args[i], stop);
// 			i++;
// 		}
// 	}
// 	else
// 		print_sorted(env);
// 	return (0);
// }

static int	skip_wsp(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		++i;
	return (i);
}

static int	get_size(char *line)
{
	int		i;
	int		j;
	int		flag;
	int		counter;
	char	tmp;

	i = 0;
	flag = 0;
	counter = 1;
	i = skip_wsp(line, i);
	while (line[i])
	{
		if (flag)
		{
			if (line[i] == tmp)
				--flag;
		}
		else
		{
			if (line[i] == '\'' || line[i] == '\"')
			{
				tmp = line[i];
				++flag;
			}
			else
			{
				j = skip_wsp(line, i);
				if (j != i)
				{
					++counter;
					i = j;
					continue ;
				}
			}
		}
		++i;
	}
	return (counter);
}

static char	*crop_line(char	*line)
{
	int		i;
	char	*tmp;

	i = 0;
	i = skip_wsp(line, i);
	tmp = line;
	line = ft_substr(line, i, ft_strlen(line) - (size_t)i);
	free(tmp);
	return (line);	
}

char	**get_params(char *line, char ***env)
{
	int		i;
	int		params_size;
	char	**params;

	line = crop_line(line);
	params_size = get_size(line);
	params = (char **)malloc(sizeof(char *) * (params_size + 1));
	i = 0;
	while (i < params_size)
	{
		
		++i;
	}
	params[params_size] = NULL;
	i = 0;
	while (params[i])
	{
		params[i] = expand(params[i], env);
		++i;
	}
	return (params);
}

int	ft_export(char **args, char ***env, char *line)
{
	int		i;
	int		stop;
	char	**params;

	(void) args;
	params = get_params(line, env);
	i = 0;
	while (params[i])
	{
		printf("%s\n", params[i]);
		i++;
	}
	printf("\n%s\n", line);
	exit(0);
	i = 1;
	if (args[i])
	{
		if (check_args(args))
		{
			write(2, "Really bad args prevent to write others\n", 40);
			return (0);
		}
		while (args[i])
		{
			stop = get_stop(args[i]);
			if (stop != -2)
				to_set_env(env, args[i], stop);
			i++;
		}
	}
	else
		print_sorted(env);
	return (0);
}
