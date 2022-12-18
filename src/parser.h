#ifndef PARSER_H
# define PARSER_H
# include "data_structures.h"
int				cmd_line(t_token **cursor, t_stack **stack);
int				piped_cmd(t_token **cursor, t_stack **stack);
int				cpl_cmd(t_token **cursor, t_stack **stack);
int				redir(t_token **cursor, t_stack **stack);
int				cmd(t_token **cursor, t_stack **stack);
int				cmd_arg(t_token **cursor, t_stack **stack);
int				redir_op(t_token **cursor, t_stack **stack);
int				cmd_suffix(t_token **cursor, t_stack **stack);
int				cmd_prefix(t_token **cursor, t_stack **stack);
#endif