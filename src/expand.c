/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/17 12:44:26 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_expantion(char *str, int i)
{
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
		&& str[j] != '$' && str[j] != '\0')
		j++;
	return (j);
}

void	expand(t_data *data, char *str, char ***env)
{
	int			i;
	t_expand	exp;

	i = 0;
	exp.counter = 0;
	exp.result = ft_strjoin("", "");
	// printf("In expand()\n");
	while((size_t)i < ft_strlen(str))
	{
		// printf("  Inside expansion\n");
		exp.start = start_expantion(str, i);
		if (exp.start == -1 && exp.counter == 0)
		{
			add_token(data, E_WORD, str);
			return ;
		}
		else if (exp.start == -1)
			break ;
		if (exp.counter == 0)
		{
			exp.tmp = exp.result;
			exp.result = ft_strjoin(exp.result, ft_substr(str, 0, exp.start));
			free(exp.tmp);
			++exp.counter;
		}
		// printf("\tBefore $ the result is: [%s]\n", exp.result);
		// printf("\tIndex of start exp: [%d]\n", exp.start);
		exp.end = end_expantion(str, exp.start + 1);
		// printf("\tIndex of end exp: [%d]\n", exp.end);
		exp.tmp = ft_substr(str, exp.start + 1, exp.end - (exp.start + 1));
		// printf("\tPart of string goes to get_env: [%s]\n", exp.tmp);
		exp.value = get_env(exp.tmp, env);
		// printf("\tValue after get_env: [%s]\n", exp.value);
		if (exp.value == NULL)
			exp.value = ft_strjoin("", "");
		free(exp.tmp);
		exp.result = ft_strjoin(exp.result, exp.value);
		// printf("\tResult after expansion: [%s]\n", exp.result);
		++exp.counter;
		free(exp.value);
		i = exp.end;
	}
	// printf("Final result: [%s]\n", exp.result);
	add_token(data, E_WORD, exp.result);
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
