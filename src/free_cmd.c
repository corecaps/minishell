/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:20:07 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/13 12:59:13 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	//need to add ast_node_free part of func
	if (data->line != NULL)
		free(data->line);
	if (data->start_token != NULL)
		del_token_list(data->start_token);
	if (data != NULL)
		free(data);
}
