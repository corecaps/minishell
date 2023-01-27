/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:58:42 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 18:00:04 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "export.h"

t_export	t_export_init(void)
{
	t_export	export;

	export.i = 0;
	export.flag = 0;
	export.counter = 1;
	export.ch_tmp = '0';
	return (export);
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

int	get_end(char *line, int start)
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
