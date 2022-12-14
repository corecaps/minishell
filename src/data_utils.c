/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:20:07 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/14 10:04:12 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->start_token = NULL;
	data->line = NULL;
	data->end = 0;
	data->index = 0;
	data->open_quote = -1;
	return (data);
}

void	free_all(t_data *data)
{
	//need to add ast_node_free part of func
	if (data->line != NULL)
		free(data->line);
	if (data->start_token != NULL)
		del_token_list(data->start_token);
	if (data != NULL)
		free(data);
	data->line = NULL;
	data->start_token = NULL;
	data = NULL;
}