/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:20:07 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/09 18:36:10 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	if (data->root)
		del_ast(data->root);
	free(data->line);
	if (data->start_token)
		del_token_list(data->start_token);
	if (data->parsing_stack)
		del_stack(data->parsing_stack);
	if (data)
		free(data);
}

/******************************************************************************
 * copy environment array into a new array
 * @param env original environment array
 * @return a freshly allocated array of environment variables
 *****************************************************************************/

char	**create_env(char **env, int argc, char **argv)
{
	char	**new_env;
	int		i;

	(void) argc;
	(void) argv;
	new_env = malloc(sizeof(char *) * (count_env(&env) + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
