/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:18:31 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/26 20:20:23 by latahbah         ###   ########.fr       */
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
 * Skip all whitespaces starting from i index of string
 * @return i - index of first non whitespace symbol
 ****************************************************************************/

static int	skip_wsp(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		++i;
	return (i);
}

/*****************************************************************************
 * Cut whitespaces from the start and the end
 * @return line without whitespaces from begin and end
 ****************************************************************************/

static char	*crop_line(char *line)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	start = skip_wsp(line, 0);
	i = start;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t'
			|| line[i] == '\n' || line[i] == '\v'
			|| line[i] == '\f' || line[i] == '\r')
			++i;
		else
		{
			end = i;
			++i;
		}
	}
	res = ft_substr(line, start, (size_t)(end - start + 1));
	return (res);
}

/*****************************************************************************
 * Count the number of args in export line command
 * @return counter - number on which we have to split export line command
 ****************************************************************************/

static t_export	t_export_init(void)
{
	t_export	export;

	export.i = 0;
	export.flag = 0;
	export.counter = 1;
	export.ch_tmp = '0';
	return (export);
}

static t_export	update_counter(t_export export)
{
	
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

/*****************************************************************************
 * Find the end index of each new arg
 * @return i - that index
 ****************************************************************************/

static int	get_end(char *line, int start)
{
	int		i;
	int		j;
	int		flag;
	char	tmp;

	i = start;
	flag = 0;
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
				if (j != i && i != start)
				{
					return (i);
				}
			}
		}
		++i;
	}
	return (i);
}

/*****************************************************************************
 * This func() has to delete needed quotes and expand vars if needed and allowed
 * @return arg which we have to put in params[i]
 ****************************************************************************/

static char	*del_quotes(char *str, char ***env)
{
	int		i;
	int		start;
	int		flag;
	char	c;
	char	*tmp;
	char	q_type;
	char	*result;

	i = 0;
	start = i;
	flag = 0;
	q_type = '0';
	result = ft_strjoin("", "");
	while(str[i])
	{
		c = str[i];
		if ((c == '\'' || c == '\"') && flag == 0)
		{
			tmp = ft_substr(str, start, (size_t)(i - start));
			// printf("\ttmp0 - [%s]\n", tmp);
			tmp = expand(tmp, env);
			// printf("\ttmp0exp - [%s]\n", tmp);
			result = add_to_res(result, tmp);
			flag = 1;
			q_type = c;
			start = i + 1;
		}
		else if ((c == '\'' || c == '\"') && flag == 1 && c == q_type)
		{
			tmp = ft_substr(str, start, (size_t)(i - start));
			// printf("\ttmp1 - [%s]\n", tmp);
			if (q_type == '\"')
				tmp = expand(tmp, env);
			// printf("\ttmp1exp - [%s]\n", tmp);
			result = add_to_res(result, tmp);
			flag = 0;
			start = i + 1;
		}
		i++;
	}
	tmp = ft_substr(str, start, (size_t)(i - start));
	// printf("\ttmp2 - [%s]\n", tmp);
	tmp = expand(tmp, env);
	// printf("\ttmp2 - [%s]\n", tmp);
	result = add_to_res(result, tmp);
	// printf("\tresult - [%s]\n", result);
	free(str);
	str = NULL;
	return (result);
}

char	**get_params(char *line, char ***env)
{
	int		i;
	int		start;
	int		end;
	int		params_size;
	char	*tmp_line;
	char	**params;

	tmp_line = crop_line(line);
	printf("Line to get_size - [%s]\n", tmp_line);
	params_size = get_size(tmp_line);
	printf("size - %d\n", params_size);
	params = (char **)malloc(sizeof(char *) * (params_size + 1));
	i = 0;
	start = 0;
	while (i < params_size)
	{
		end = get_end(tmp_line, start);
		params[i] = ft_substr(tmp_line, start, (size_t)(end - start));
		// printf("params[%d] = [%s]\n", i, params[i]);
		params[i] = del_quotes(params[i], env);
		// printf("params[%d] = [%s]\n", i, params[i]);
		start = skip_wsp(tmp_line, end);
		++i;
	}
	params[params_size] = NULL;
	// exit(0);
	// i = 0;
	// while (params[i])
	// {
	// 	printf("[%s]\n", params[i]);
	// 	i++;
	// }
	// printf("finish\n");
	// exit(0);
	//
	free(tmp_line);
	return (params);
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

int	ft_export(char **args, char ***env, char *line)
{
	int		i;
	int		stop;
	char	**params;

	(void) args;
	params = get_params(line, env);
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
