/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:34:48 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/11 13:52:49 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "data_structures.h"

static void	get_token_type(t_token *token)
{
	//printf("First char = %c\n", token->value[0]);
	if (token->value[0] == '|')
		token->token_type = E_PIPE;
	else if (token->value[0] == '<' && (int)ft_strlen(token->value) == 2)
		token->token_type = E_HEREDOC;
	else if (token->value[0] == '<')
		token->token_type = E_INFILE;
	else if (token->value[0] == '>' && (int)ft_strlen(token->value) == 2)
		token->token_type = E_APPEND;
	else if (token->value[0] == '>')
		token->token_type = E_OUTFILE;
	else if (token->value[0] == '\'')
		token->token_type = E_SINGLE_QUOTED;
	else if (token->value[0] == '\"')
		token->token_type = E_DOULE_QUOTED;
	else
		token->token_type = E_WORD;
}

static void	token_init(t_data *data)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	//typisation_and_expansion.c
	//printf("After\nIndex = %d\nEnd = %d\n", data->index, data->end);
	token->value = ft_substr(data->line, data->index, data->end - data->index);
	if (!token->value)
		exit(EXIT_FAILURE);
	get_token_type(token);
	//
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
	data->end++;
}

static void	common_token(t_data *data)
{
	// printf("\nBefore\nIndex = %d\nEnd = %d\n", data->index, data->end);
	// printf("Cur char = %c\n", data->line[data->end]);
	while (data->line[data->end] > 32 && data->line[data->end] < 127)
		data->end++;
	token_init(data);
}

static void	pipe_token(t_data *data)
{
	char	*tmp;

	token_init(data);
	tmp = data->cur_token->value;
	data->cur_token->value = "|";
	free(tmp);
	data->end++;
}

static void	redirect_token(t_data *data)
{
	if (data->line[data->end] == '>' && data->line[data->end + 1] == '>')
	{
		data->end += 2;
		token_init(data);
	}
	else if (data->line[data->end] == '<' && data->line[data->end + 1] == '<')
	{
		data->end += 2;
		token_init(data);
	}
	else if (data->line[data->end] == '>')
	{
		data->end += 1;
		token_init(data);
	}
	else
	{
		data->end += 1;
		token_init(data);
	}
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
		else if (data->line[data->end] == '>' || data->line[data->end] == '<')
			redirect_token(data);
		else if (data->line[data->end] == '|')
			pipe_token(data);
		else
			common_token(data);
		printf("Token->value: %s\n", data->cur_token->value);
		printf("Token->token_type: %u\n\n", data->cur_token->token_type);
	}
}
