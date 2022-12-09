/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:13:13 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/07 12:46:43 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

typedef enum e_token_type {
	E_WORD,
	E_PIPE,
	E_HEREDOC,
	E_APPEND,
	E_INFILE,
	E_OUTFILE,
	E_SINGLE_QUOTED,
	E_DOULE_QUOTED
}	t_token_type;

typedef struct s_token
{
	t_token_type 	token_type;
	char			*value;
	struct s_token	*next_token;
}	t_token;

typedef struct s_ast
{
	t_token			*token_node;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_data
{
	char	*line;
	t_token	*token;
}	t_data;

#endif