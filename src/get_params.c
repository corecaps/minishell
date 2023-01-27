/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:02:01 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 18:04:11 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "export.h"

int	skip_wsp(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		++i;
	return (i);
}

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

char	**get_params(char *line, char ***env, int i, int start)
{
	int		end;
	int		params_size;
	char	*tmp_line;
	char	**params;

	tmp_line = crop_line(line);
	params_size = get_size(tmp_line);
	params = (char **)malloc(sizeof(char *) * (params_size + 1));
	i = 0;
	start = 0;
	while (i < params_size)
	{
		end = get_end(tmp_line, start);
		params[i] = ft_substr(tmp_line, start, (size_t)(end - start));
		params[i] = del_quotes(params[i], env);
		start = skip_wsp(tmp_line, end);
		++i;
	}
	params[params_size] = NULL;
	free(tmp_line);
	return (params);
}
