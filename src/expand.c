/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/10 20:09:35 by latahbah         ###   ########.fr       */
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
	t_expand	*exp;
	char		*result;
	char		*value;
	char		*tmp;

	exp = malloc(sizeof(t_expand));
	exp->start = start_expantion(str);
	if (exp->start == -1)
		return (str);
	exp->end = end_expantion(str, exp->start);
	tmp = ft_substr(str, exp->start + 1, exp->end - (exp->start + 1));
	printf("tmp = [%s]\n", tmp);
	exit(0);
	value = get_env(tmp, env);
	if (value == NULL)
		value = "";
	free(tmp);
	result = ft_substr(str, 0, (size_t)exp->start);
	result = ft_strjoin(result, value);
	free(tmp);
	free(value);
	value = ft_substr(str, exp->end, ft_strlen(str) - (size_t)exp->end);
	tmp = result;
	result = ft_strjoin(result, value);
	free(tmp);
	free(value);
	free(str);
	free(exp);
	return (result);
}
