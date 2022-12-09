/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:34:48 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/08 17:55:47 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "data_structures.h"

static char	*quotated_word(t_data *data)
{
	char	*start_char;
	int		value_len;

	value_len = 1;
	start_char = data->line;
	data->line++;
	while (*data->line != *start_char && *data->line)
	{
		value_len++;
		data->line++;
	}
	if (!*data->line)
		exit(EXIT_FAILURE);
	value_len++;
	data->line++;
	return (ft_substr(start_char, 0, value_len));
}	

static char	*common_word(t_data *data)
{
	char	*start_value;
	int		value_len;

	value_len = 0;
	start_value = data->line;
	while (*data->line != ' ' && *data->line)
	{
		value_len++;
		data->line++;
	}
	if (*data->line)
		data->line++;
	return (ft_substr(start_value, 0, value_len));
}

static char	*get_token_value(t_data *data)
{
	char	*result;

	if (*data->line == '\'' || *data->line == '\"')
		result = quotated_word(data);
	else
		result = common_word(data);
	return (result);
}

static void	token_init(t_data *data)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = get_token_value(data);
	if (!token->value)
		exit(EXIT_FAILURE);
	if (!data->start_token)
		data->start_token = token;
	else
		data->cur_token->next_token = token;
	data->cur_token = token;
}

void	get_tokens(t_data *data)
{
	while (*data->line)
	{
		token_init(data);
	}
}
