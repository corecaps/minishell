/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:36:34 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/09 18:36:54 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H
# include "data_structures.h"

typedef struct s_ast_builder
{
	t_ast	*root;
	t_ast	*current;
}	t_ast_builder;
int				cmd_line(t_token **cursor, t_data *data);
int				piped_cmd(t_token **cursor, t_data *data);
int				cpl_cmd(t_token **cursor, t_data *data);
int				redir(t_token **cursor, t_data *data);
int				cmd(t_token **cursor, t_data *data);
int				cmd_arg(t_token **cursor, t_data *data);
int				redir_op(t_token **cursor, t_data *data);
int				cmd_suffix(t_token **cursor, t_data *data);
int				cmd_prefix(t_token **cursor, t_data *data);
int				create_redir_node(t_data *data, t_token *token);
int				create_cmd_node(t_data *data, t_token *token);
int				create_pipe_node(t_data *data, t_token *token);
int				create_cmd_arg_node(t_data *data, t_token *token);
#endif