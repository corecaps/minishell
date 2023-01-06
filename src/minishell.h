/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:55 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/20 10:48:29 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include "data_structures.h"
# include "lexer.h"
# define PS1 "\033[0;32mMinishell\t\033[0m$"

void			add_token(t_data *data, t_token_type type, char *value);
int				count_token(t_token *head);
void			get_bottom(t_token *head, t_token *new_node);
void			del_token_list(t_token *head);
t_ast			*add_left(t_ast *parent, t_token *token);
t_ast			*add_right(t_ast *parent, t_token *token);
t_ast			*get_top(t_ast *node);
t_token_type	peek(t_stack *head);
t_token_type	pop(t_stack **head);
t_stack			*push(t_token_type type, t_stack *head);
void			del_ast(t_ast *top);
// t_data			*data_init(void);
void			free_all(t_data *data);
void			del_stack(t_stack *head);
int				count_stack(t_stack *head);
int				parse(t_data *data);
void			print_debug(t_token_type type);
char			**get_path();
char			*find_binary(char *name);
char			**get_args(t_ast *command_node);
int				traverse_ast(t_ast *current_node, char ***env);
size_t			count_env(char ***env);
char			**create_env(char **env, int argc, char **argv);
char			*get_env(char *key,char **env);
#endif