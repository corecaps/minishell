/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:35:33 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/09 18:21:59 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "data_structures.h"

void	lexer(t_data *data);
void	skip_whitespaces(t_data *data);
void	add_pipe_token(t_data *data);
void	add_redirect_token(t_data *data);
void	add_word_token(t_data *data, char sep);
void	add_quoted_token(t_data *data);
#endif