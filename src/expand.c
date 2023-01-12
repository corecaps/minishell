/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/12 13:04:27 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_expantion(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
	{
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

static int	end_expantion(char *str, int start)
{
	int	j;

	j = start;
	while (str[j] != ' ' && str[j] != '|'
		&& str[j] != '>' && str[j] != '<'
		&& str[j] != '\'' && str[j] != '\"'
		&& str[j] != '\0')
		j++;
	return (j);
}

char	*expand(char *str, char ***env)
{
	t_expand	exp;
	char		*result;

	exp.start = start_expantion(str);
	if (exp.start == -1)
		return (str);
	exp.end = end_expantion(str, exp.start);
	exp.tmp = ft_substr(str, exp.start + 1, exp.end - (exp.start + 1));
	exp.value = get_env(exp.tmp, env);
	if (exp.value == NULL)
		exp.value = ft_strjoin("", "");
	free(exp.tmp);
	exp.tmp = ft_substr(str, 0, (size_t)exp.start);
	result = ft_strjoin(exp.tmp, exp.value);
	free(exp.tmp);
	free(exp.value);
	exp.value = ft_substr(str, exp.end, ft_strlen(str) - (size_t)exp.end);
	exp.tmp = result;
	result = ft_strjoin(result, exp.value);
	free(exp.tmp);
	free(exp.value);
	free(str);
	return (result);
}
