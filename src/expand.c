/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/18 11:19:43 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_to_res(char *curr_res, char *add_word)
{
	char	*res;

	res = ft_strjoin(curr_res, add_word);
	free(curr_res);
	free(add_word);
	return (res);
}

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
	return res;
}

char	*expand(char *str, char ***env)
{
	int		i;
	int 	start;
	char	*result;
	char	*tmp;

	i = 0;
	start = i;
	result = ft_strjoin("", "");
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, start, i - start);
			// printf("\ttmp = [%s]\n", tmp);
			tmp = retrieve_str(tmp, env);
			// printf("\tmtmp = [%s]\n", tmp);
			result = add_to_res(result, tmp);
			start = i;
		}
		if (str[i + 1] == '\0')
		{
			tmp = ft_substr(str, start, i - start + 1);
			// printf("\ttmp = [%s]\n", tmp);
			tmp = retrieve_str(tmp, env);
			// printf("\tmtmp = [%s]\n", tmp);
			result = add_to_res(result, tmp);
			start = i;
		}
		++i;
	}
	// printf("\tresult = [%s]\n", result);
	//result = add_to_res("", ft_strjoin("",""));
	free(str);
	return (result);
}

// char	*expand(char *str, char ***env)
// {
// 	t_expand	exp;
// 	char		*result;

// 	exp.start = start_expantion(str, 0);
// 	if (exp.start == -1)
// 		return (str);
// 	exp.end = end_expantion(str, exp.start);
// 	exp.tmp = ft_substr(str, exp.start + 1, exp.end - (exp.start + 1));
// 	exp.value = get_env(exp.tmp, env);
// 	if (exp.value == NULL)
// 		exp.value = ft_strjoin("", "");
// 	free(exp.tmp);
// 	exp.tmp = ft_substr(str, 0, (size_t)exp.start);
// 	result = ft_strjoin(exp.tmp, exp.value);
// 	free(exp.tmp);
// 	free(exp.value);
// 	exp.value = ft_substr(str, exp.end, ft_strlen(str) - (size_t)exp.end);
// 	exp.tmp = result;
// 	result = ft_strjoin(result, exp.value);
// 	free(exp.tmp);
// 	free(exp.value);
// 	free(str);
// 	return (result);
// }
