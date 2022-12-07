/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:13:13 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/07 12:36:19 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

typedef enum e_token {
	word,
	pipe,
	heredoc,
	append,
	in,
	out,
	sinqle_qoute,
	double_quote
}	t_token;

typedef struct s_token
{
	t_token			token_type; // never used enums, maybe here is should be *token_type??
	char			*value;
	struct s_token	*next_token;
}	t_token;

typedef struct s_ast
{
	t_token			*token_node;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

#endif