/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:20:44 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/12 12:07:39 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "data_structures.h"

void	add_pipe_token(t_data *data)
{
	add_token(data, E_PIPE, "|");
	data->end++;
}

void	add_redirect_token(t_data *data)
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
			add_token(data, E_OUTFILE, ">");
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
			add_token(data, E_INFILE, "<");
	}
	data->end++;
}

static void	get_end_index(t_data *data)
{
	while ((data->line[data->end] != ' ' && data->line[data->end] != '\t'
			&& data->line[data->end] != '\n' && data->line[data->end] != '>'
			&& data->line[data->end] != '\v' && data->line[data->end] != '<'
			&& data->line[data->end] != '\f' && data->line[data->end] != '|'
			&& data->line[data->end] != '\r'
			&& data->line[data->end] != '\''
			&& data->line[data->end] != '"')
		&& data->line[data->end] != 0)
		data->end++;
}

void	add_word_token(t_data *data, char sep, char ***env)
{
	char	*rawvalue;
	char	*value;

	skip_whitespaces(data);
	data->index = data->end;
	if (sep == ' ')
		get_end_index(data);
	else
		while (data->line[data->end] != sep && data->line != 0)
			data->end++;
	rawvalue = ft_substr(data->line, data->index, data->end - data->index);
	if (!rawvalue)
		exit(EXIT_FAILURE);
	if (sep == ' ' || sep == '\"')
	{
		value = expand(rawvalue, env);
		add_token(data, E_WORD, value);
	}
	else
	{
		add_token(data, E_WORD, rawvalue);
	}
}

void	add_quoted_token(t_data *data, char ***env)
{
	char	sep;

	if (data->line[data->end] == '\'')
	{
		add_token(data, E_SINGLE_QUOTE, "\'");
		sep = '\'';
	}
	else
	{
		add_token(data, E_DOULE_QUOTE, "\"");
		sep = '\"';
	}
	data->open_quote *= -1;
	data->end++;
	data->index = data->end;
	if (data->line[data->end] && data->open_quote > 0
		&& data->line[data->end] != sep)
		add_word_token(data, sep, env);
}
