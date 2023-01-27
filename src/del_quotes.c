/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:53:41 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 17:57:16 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "export.h"

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

char	*del_quotes(char *str, char ***env)
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
