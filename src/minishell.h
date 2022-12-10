/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:19:55 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/07 12:56:19 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "data_structures.h"
# define PS1 "\033[0;32mMinishell\t\033[0m$"

t_token			*add_token(t_token *head, t_token_type type, char *value);
int				count_token(t_token *head);
void			del_token_list(t_token *head);
t_ast			*add_left(t_ast *parent, t_token *token);
t_ast			*add_right(t_ast *parent, t_token *token);
t_ast			*get_top(t_ast *node);
void			del_ast(t_ast *top);
int				count_stack(t_stack *head);
t_token_type	peek(t_stack *head);
t_token_type	pop(t_stack **head);
t_stack			*push(t_token_type type, t_stack *head);
void			del_stack(t_stack *head);
#endif