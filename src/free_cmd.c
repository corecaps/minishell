/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:20:07 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/12 17:15:26 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	//need to add ast_node_free part of func
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->start_token)
	{
		del_token_list(data->start_token);
		data->start_token = NULL;
	}
	if (data)
		free(data);
}