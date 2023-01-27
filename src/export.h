/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:33:32 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 18:04:20 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

typedef struct s_export
{
	int		i;
	int		j;
	int		flag;
	char	ch_tmp;
	int		counter;
}t_export;

typedef struct s_exp_dyn
{
	int		i;
	int		start;
	int		flag;
	char	c;
	char	q_type;
	char	*tmp;
	char	*result;
}	t_exp_dyn;

t_export	t_export_init(void);
int			skip_wsp(char *str, int i);
int			get_end(char *line, int start);
char		*del_quotes(char *str, char ***env);
char		**get_params(char *line, char ***env, int i, int start);

#endif