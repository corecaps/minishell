/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:55 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 15:16:49 by latahbah         ###   ########.fr       */
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

void			add_token(t_data *data, t_token_type type, char *value);
void			get_bottom(t_token *head, t_token *new_node);
t_token_type	pop(t_stack **head);
t_stack			*push(t_token_type type, t_stack *head);
char			*expand(char *str, char ***env);
int				count_stack(t_stack *head);
int				parse(t_data *data);
char			*find_binary(char *name);
char			**get_args(t_ast *command_node);
int				count_env(char ***env);
int				is_dir(const char *path);
int				create_env(char **env, int argc, char **argv);
char			*get_env(char *key, char ***env);
t_garbage		**gc_add(void *ptr);
void			gc_free(void);
void			*gc_alloc(size_t nmemb, size_t size);
int				gc_del(void *ptr);
int				set_env(char *key, char *value);
t_ast			*ast_node_init(t_token *token, t_token_type token_type);
void			set_signals(void);
void			reset_signals(void);
int				parse_here_doc(t_ast *node);
int				exec_cmd_line(t_ast *current_node, char ***env, char *line);
void			print_sorted(char ***env_pointer);
char			*get_prompt(char ***env);
void			parser_error(int status);
void			exec_error(int status);
char			*add_to_res(char *curr_res, char *add_word);
int				gc_check_double(t_garbage *gc, void *ptr);
char			***gc_env_alloc(int size);
t_garbage		**gc_env_add(void *ptr);
int				gc_env_del(void *ptr);
void			gc_env_free(void);

#endif