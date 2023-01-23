/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/23 10:04:24 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************
 * Add expanded value to final result
 ****************************************************************************/

static char	*add_to_res(char *curr_res, char *add_word)
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
	return (exp);
}

/*****************************************************************************
 * Get expanded part of word
 ****************************************************************************/

char	*get_exp_tmp(char *str, int start, int len, char ***env)
{
	char	*tmp;

	tmp = ft_substr(str, start, len);
	tmp = retrieve_str(tmp, env);
	return (tmp);
}

/*****************************************************************************
 * Check and expand word token with $
 ****************************************************************************/

char	*expand(char *str, char ***env)
{
	t_exp	exp;
	char	*result;
	char	*tmp;

	exp = exp_init(0);
	result = ft_strjoin("", "");
	while (str[exp.i])
	{
		if (str[exp.i] == '$')
		{
			tmp = get_exp_tmp(str, exp.start, exp.i - exp.start, env);
			result = add_to_res(result, tmp);
			exp.start = exp.i;
		}
		if (str[exp.i + 1] == '\0')
		{
			tmp = get_exp_tmp(str, exp.start, exp.i - exp.start + 1, env);
			result = add_to_res(result, tmp);
			exp.start = exp.i;
		}
		++exp.i;
	}
	free(str);
	return (result);
}
