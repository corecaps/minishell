/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:18:31 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/25 23:39:55 by latahbah         ###   ########.fr       */
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
	char	*tmp;

	start = skip_wsp(line, 0);
	tmp = line;
	i = start;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t'
		|| line[i] == '\n' || line[i] == '\v'
		|| line[i] == '\f' || line[i]== '\r')
			++i;
		else
		{
			end = i;
			++i;
		}
		
	}
	line = ft_substr(line, start, (size_t)(end - start + 1));
	free(tmp);
	return (line);
}

/*****************************************************************************
 * Count the number of args in export line command
 * @return counter - number on which we have to split export line command
 ****************************************************************************/

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
	int		flag;
	int		start;
	int		counter;
	char	tmp;
	char	*result;
	char	*res_tmp;
	char	*value;
	int		exp_flag = 1;

	i = 0;
	flag = 0;
	counter = 0;
	start = 0;
	result = ft_strjoin("","");
	res_tmp = result;
	while (str[i])
	{
		if (flag)
		{
			if ((str[i] == '\'' || str[i] == '\"') && str[i] == tmp)
			{
				value = ft_substr(str, start + 1, (size_t)(i - start - 1));
				printf("\tvalueo before exp: [%s]\n", value);
				if (exp_flag)
					value = expand(value, env);
				printf("\tvalue0 after exp: [%s]\n", value);
				result = ft_strjoin(result, value);
				free(res_tmp);
				res_tmp = result;
				if (str[i] == '\'')
					exp_flag = 1;
				flag = 0;
				start = i;
			}
			else
				++counter;
		}
		else
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				if (i != 0)
				{
					value = ft_substr(str, start + 1, (size_t)(i - start - 1));
					printf("\tvalue before exp: [%s]\n", value);
					if (exp_flag)
						value = expand(value, env);
					// printf("\ti = %d, start = %d\n", i, start);
					// printf("\tresult before: [%s]\n", result);
					printf("\tvalue1 after exp: [%s]\n", value);
					result = ft_strjoin(result, value);
					free(res_tmp);
					res_tmp = result;
				}
				tmp = str[i];
				flag = 1;
				if (tmp == '\'')
					exp_flag = 0;
				start = i;
			}
			else
				++counter;
		}
		++i;
	}
	if (!ft_strncmp(result, "", 1))
	{
		value = ft_substr(str, start, (size_t)(i - start));
		if (exp_flag)
			value = expand(value, env);
		printf("\tvalue2: [%s]\n", value);
		result = ft_strjoin(result, value);
		free(value);
		free(res_tmp);
	}
	free(str);
	return (result);
}

char	**get_params(char *line, char ***env)
{
	int		i;
	int		start;
	int		end;
	int		params_size;
	char	**params;

	line = crop_line(line);
	params_size = get_size(line);
	printf("size - %d\n", params_size);
	params = (char **)malloc(sizeof(char *) * (params_size + 1));
	i = 0;
	start = 0;
	while (i < params_size)
	{
		end = get_end(line, start);
		params[i] = ft_substr(line, start, (size_t)(end - start));
		printf("params[%d] = [%s]\n", i, params[i]);
		params[i] = del_quotes(params[i], env);
		printf("params[%d] = [%s]\n", i, params[i]);
		start = skip_wsp(line, end);
		++i;
	}
	params[params_size] = NULL;
	exit(0);
	i = 0;
	while (params[i])
	{
		printf("[%s]\n", params[i]);
		i++;
	}
	printf("finish\n");
	exit(0);
	//
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
