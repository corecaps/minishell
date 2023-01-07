/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:13:13 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/22 14:47:17 by latahbah         ###   ########.fr       */
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
	E_SINGLE_QUOTE,
	E_DOULE_QUOTE,
	E_EPSILON,
	E_NON_TERMINALS,
	E_COMMAND_LINE,
	E_PIPED_COMMAND,
	E_COMPLETE_COMMAND,
	E_COMMAND_PREFIX,
	E_COMMAND_SUFFIX,
	E_REDIRECTION,
	E_COMMAND,
	E_COMMAND_ARG,
	E_REDIRECTION_OP,
	E_END_OF_TOKEN
}	t_token_type;

typedef int		(*t_f_builtin)(char **args, char **env);


typedef struct s_here_doc {
	char	*line;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
	struct s_token	*next_token;
}	t_token;

typedef struct s_ast
{
	t_token			*token_node;
	t_token_type	type;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	int				in_pipe;
	int				out_pipe;
	int				here_doc;
	int				forked;
	t_here_doc		*here_doc_list;
}	t_ast;

typedef struct s_stack
{
	t_token_type	type;
	struct s_stack	*next;
}	t_stack;

typedef struct s_data
{
	int		index;
	int		end;
	int		open_quote;
	char	*line;
	t_token	*start_token;
	t_ast	*root;
	t_ast	*current;
	t_stack	*parsing_stack;
}	t_data;

#endif