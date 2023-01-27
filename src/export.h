/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:33:32 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/27 15:03:11 by latahbah         ###   ########.fr       */
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

#endif