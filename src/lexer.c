/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:34:48 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/14 10:32:13 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "data_structures.h"

static void	skip_whitespaces(t_data *data)
{
	while (data->line[data->end] == ' ' || data->line[data->end] == '\t'
		|| data->line[data->end] == '\n' || data->line[data->end] == '\v'
		|| data->line[data->end] == '\f' || data->line[data->end] == '\r')
		data->end++;
}

static void	add_pipe_token(t_data *data)
{
	add_token(data, E_PIPE, "|");
	data->end++;
}

static void	add_redirect_token(t_data *data)
{
	if (data->line[data->end] == '>')
	{
		if (data->line[data->end + 1] != 0
			&& data->line[data->end + 1] == '>')
		{
			add_token(data, E_APPEND, ">>");
			data->end += 1;
		}
		else
			add_token(data, E_INFILE, ">");
	}
	else
	{
		if (data->line[data->end + 1] != 0
			&& data->line[data->end + 1] == '<')
		{
			add_token(data, E_HEREDOC, "<<");
			data->end += 1;
		}
		else
			add_token(data, E_OUTFILE, "<");
	}
	data->end++;
}

static void	add_word_token(t_data *data, char sep)
{
	char	*value;

	data->index = data->end;
	if (sep == ' ')
		while ((data->line[data->end] != ' ' && data->line[data->end] != '\t'
				&& data->line[data->end] != '\n' && data->line[data->end] != '>'
				&& data->line[data->end] != '\v' && data->line[data->end] != '<'
				&& data->line[data->end] != '\f' && data->line[data->end] != '|'
				&& data->line[data->end] != '\r')
			&& data->line[data->end] != 0)
			data->end++;
	else
		while (data->line[data->end] != sep && data->line != 0)
			data->end++;
	value = ft_substr(data->line, data->index, data->end - data->index);
	if (!value)
		exit(EXIT_FAILURE);
	add_token(data, E_WORD, value);
}

static void	add_quoted_token(t_data *data)
{
	char	sep;

	if (data->line[data->end] == '\'')
	{
		add_token(data, E_SINGLE_QUOTED, "\'");
		sep = '\'';
	}
	else
	{
		add_token(data, E_DOULE_QUOTED, "\"");
		sep = '\"';
	}
	data->open_quote *= -1;
	data->end++;
	data->index = data->end;
	if (data->line[data->end] && data->open_quote > 0
		&& data->line[data->end] != '\"'
		&& data->line[data->end] != '\'')
		add_word_token(data, sep);
}

void	lexer(t_data *data)
{
	data->end = 0;
	while (data->end < (int)ft_strlen(data->line))
	{
		skip_whitespaces(data);
		data->index = data->end;
		if (data->line[data->end] == '|')
			add_pipe_token(data);
		else if (data->line[data->end] == '>' || data->line[data->end] == '<')
			add_redirect_token(data);
		else if (data->line[data->end] == '\'' || data->line[data->end] == '\"')
			add_quoted_token(data);
		else if (data->line[data->end] > 32 && data->line[data->end] < 127)
			add_word_token(data, ' ');
		else
			break ;
	}
}
