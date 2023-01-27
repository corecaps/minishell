/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 12:49:18 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************
 * Add expanded value to final result
 ****************************************************************************/

char	*add_to_res(char *curr_res, char *add_word)
{
	char	*res;

	res = ft_strjoin(curr_res, add_word);
	free(curr_res);
	free(add_word);
	return (res);
}

/*****************************************************************************
 * Retrieve expand vaue from env
 ****************************************************************************/

static char	*retrieve_str(char *tmp, char ***env)
{
	char	*res;

	if (tmp[0] == '$')
	{
		res = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
		if (res == NULL)
			res = ft_strjoin("", "");
		free(tmp);
		tmp = res;
		res = get_env(res, env);
		if (res == NULL)
			res = ft_strjoin("", "");
		free(tmp);
	}
	else
	{
		res = ft_strjoin("", tmp);
		free(tmp);
	}
	return (res);
}

/*****************************************************************************
 * Initialisation of indexes to norme
 ****************************************************************************/

t_exp	exp_init(int i)
{
	t_exp	exp;

	exp.i = i;
	exp.start = i;
	exp.flag = 0;
	return (exp);
}

/*****************************************************************************
 * Check and expand word token with $
 ****************************************************************************/

char	*expand(char *str, char ***env)
{
	t_exp	exp;
	char	*result;
	char	*tmp;
	char	c;

	exp = exp_init(0);
	result = ft_strjoin("", "");
	while (str[exp.i])
	{
		c = str[exp.i];
		if (c == '$' || c == ' ' || c == '\t' || c == '='
			|| c == '\n' || c == '\v' || c == '\f' || c == '\r')
		{
			tmp = ft_substr(str, exp.start, (size_t)(exp.i - exp.start));
			if (exp.flag == 1)
				tmp = retrieve_str(tmp, env);
			result = add_to_res(result, tmp);
			exp.start = exp.i;
			if (c == '$')
				exp.flag = 1;
			else
				exp.flag = 0;
		}
		++exp.i;
	}
	tmp = ft_substr(str, exp.start, (size_t)(exp.i - exp.start));
	if (exp.flag == 1)
	{
		tmp = retrieve_str(tmp, env);
	}
	result = add_to_res(result, tmp);
	free(str);
	return (result);
}
