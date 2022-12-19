#ifndef PARSER_H
# define PARSER_H
# include "data_structures.h"
typedef struct s_ast_builder
{
	t_ast	*root;
	t_ast	*current;
} t_ast_builder;
int				cmd_line(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				piped_cmd(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				cpl_cmd(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				redir(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				cmd(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				cmd_arg(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				redir_op(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				cmd_suffix(t_token **cursor, t_stack **stack,t_ast_builder *ast);
int				cmd_prefix(t_token **cursor, t_stack **stack,t_ast_builder *ast);
#endif