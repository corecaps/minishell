/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:35:29 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/22 16:43:34 by latahbah         ###   ########.fr       */
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

char	*expand(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	*value;
	char	*tmp;

	i = start_expantion(str);
	if (i == -1)
		return (str);
	j = end_expantion(str, i);
	tmp = ft_substr(str, i + 1, j - (i + 1));
	value = getenv(tmp);
	if (value == NULL)
		value = "";
	free(tmp);
	result = ft_substr(str, 0, (size_t)i);
	tmp = result;
	result = ft_strjoin(result, value);
	free(tmp);
	value = ft_substr(str, j, ft_strlen(str) - (size_t)j);
	tmp = result;
	result = ft_strjoin(result, value);
	free(tmp);
	free(value);
	free(str);
	return (result);
}
