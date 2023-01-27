/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 02:18:31 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 13:34:44 by latahbah         ###   ########.fr       */
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

static t_export	update_counter(char *line, t_export vars)
{
	if (vars.flag)
	{
		if (line[vars.i] == vars.ch_tmp)
			--vars.flag;
	}
	else
	{
		if (line[vars.i] == '\'' || line[vars.i] == '\"')
		{
			vars.ch_tmp = line[vars.i];
			++vars.flag;
		}
		else
		{
			vars.j = skip_wsp(line, vars.i);
			if (vars.j != vars.i)
			{
				++vars.counter;
				vars.i = vars.j;
				return (vars);
			}
		}
	}
	++vars.i;
	return (vars);
}

static int	get_size(char *line)
{
	t_export	vars;

	vars = t_export_init();
	while (line[vars.i])
	{
		vars = update_counter(line, vars);
	}
	return (vars.counter);
}

/*****************************************************************************
 * Find the end index of each new arg
 * @return i - that index
 ****************************************************************************/

static t_export	find_end(char *line, t_export vars, int start)
{
	if (vars.flag)
	{
		if (line[vars.i] == vars.ch_tmp)
			--vars.flag;
	}
	else
	{
		if (line[vars.i] == '\'' || line[vars.i] == '\"')
		{
			vars.ch_tmp = line[vars.i];
			++vars.flag;
		}
		else
		{
			vars.j = skip_wsp(line, vars.i);
			if (vars.j != vars.i && vars.i != start)
			{
				vars.counter = 0;
				return (vars);
			}
		}
	}
	return (vars);
}

static int	get_end(char *line, int start)
{
	t_export	vars;

	vars = t_export_init();
	vars.i = start;
	while (line[vars.i])
	{
		vars = find_end(line, vars, start);
		if (vars.counter == 0)
			return (vars.i);
		++vars.i;
	}
	return (vars.i);
}

static t_exp_dyn	*t_exp_dyn_init(void)
{
	t_exp_dyn	*dvars;

	dvars = malloc(sizeof(t_exp_dyn));
	dvars->i = 0;
	dvars->start = 0;
	dvars->flag = 0;
	dvars->q_type = '0';
	dvars->tmp = NULL;
	dvars->result = NULL;
	return (dvars);
}

/*****************************************************************************
 * This func() has to delete needed quotes and expand vars if needed and allowed
 * @return arg which we have to put in params[i]
 ****************************************************************************/

static void	update_res(t_exp_dyn *dvars, char *str, char ***env)
{
	dvars->tmp = ft_substr(str, dvars->start,
			(size_t)(dvars->i - dvars->start));
	if (dvars->flag == 0 || (dvars->flag == 1 && dvars->q_type == '\"')
		|| str[dvars->i] == '\0')
		dvars->tmp = expand(dvars->tmp, env);
	dvars->result = add_to_res(dvars->result, dvars->tmp);
	if (dvars->flag == 0)
	{
		dvars->flag = 1;
		dvars->q_type = dvars->c;
	}
	else if (dvars->flag == 1)
	{
		dvars->flag = 0;
		dvars->q_type = '0';
	}
	dvars->start = dvars->i + 1;
}

static char	*del_quotes(char *str, char ***env)
{
	t_exp_dyn	*dvars;
	char		*res;

	dvars = t_exp_dyn_init();
	dvars->result = ft_strjoin("", "");
	while (str[dvars->i])
	{
		dvars->c = str[dvars->i];
		if ((dvars->c == '\'' || dvars->c == '\"') && dvars->flag == 0)
			update_res(dvars, str, env);
		else if ((dvars->c == '\'' || dvars->c == '\"')
			&& dvars->flag == 1 && dvars->c == dvars->q_type)
			update_res(dvars, str, env);
		dvars->i++;
	}
	update_res(dvars, str, env);
	res = ft_strdup(dvars->result);
	free(dvars->result);
	free(dvars);
	free(str);
	str = NULL;
	return (res);
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
	//test
	i = 0;
	printf("PRINT PARAMS:\n");
	while (params[i])
	{
		printf("[%s]\n", params[i]);
		++i;
	}
	//
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
