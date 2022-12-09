/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:34:48 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/09 14:53:07 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "data_structures.h"

static void	token_init(t_data *data)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = ft_substr(data->line, data->index, data->end - data->index);
	printf("Token->value: %s\n", token->value);
	if (!token->value)
		exit(EXIT_FAILURE);
	if (!data->start_token)
		data->start_token = token;
	else
		data->cur_token->next_token = token;
	data->cur_token = token;
}

static void	quotated_token(t_data *data)
{
	char	separator;

	separator = data->line[data->index];
	data->end++;
	while (data->line[data->end] != separator && data->line[data->end] != 0)
	{
		data->end++;
	}
	if (data->line[data->end] == 0)
		exit(EXIT_FAILURE);
	else if (data->end == data->index + 1)
		return ;
	else
	{
		data->end++;
		token_init(data);
		data->end--;
	}
}

static void	common_token(t_data *data)
{
	data->end++;
	while (data->line[data->end] > 32 && data->line[data->end] < 127)
		data->end++;
	if (data->end == data->index + 1)
		return ;
	else
		token_init(data);
}

void	lexer(t_data *data)
{
	data->end = 0;
	while (data->end < (int)ft_strlen(data->line))
	{
		while (data->line[data->end] == ' ' || data->line[data->end] == '\t'
			|| data->line[data->end] == '\n' || data->line[data->end] == '\v'
			|| data->line[data->end] == '\f' || data->line[data->end] == '\r')
			data->end++;
		data->index = data->end;
		if (data->line[data->end] == '\'' || data->line[data->end] == '\"')
			quotated_token(data);
		else
			common_token(data);
		data->end++;
	}
}
