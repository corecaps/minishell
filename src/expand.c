/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/26 11:11:02 by latahbah         ###   ########.fr       */
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
	exp.flag = 0;
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
	char	c;

	exp = exp_init(0);
	result = ft_strjoin("", "");
	printf("str to exp - [%s]\n", str);
	while (str[exp.i])
	{
		if (str[exp.i] == '$')
		{
			tmp = ft_substr(str, exp.start, (size_t)(exp.i - exp.start));
			printf("\ttmp to add before $ - [%s]\n", tmp);
			result = add_to_res(result, tmp);
			exp.start = exp.i + 1;
			exp.flag  = 1;
		}
		c = str[exp.i];
		if ((c == ' ' || c == '\t'
			|| c == '\n' || c == '\v'
			|| c == '\f' || c == '\r') && exp.flag)
		{
			printf("\ttmp before exp - [%s]\n", tmp);
			tmp = get_exp_tmp(str, exp.start, exp.i - exp.start, env);
			printf("\ttmp after exp - [%s]\n", tmp);
			result = add_to_res(result, tmp);
			exp.start = exp.i;
			exp.flag = 0;
		}
		++exp.i;
	}
	tmp = get_exp_tmp(str, exp.start, exp.i - exp.start, env);
	result = add_to_res(result, tmp);
	free(str);
	printf("result - [%s]\n", result);
	return (result);
}
