/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:20:07 by latahbah          #+#    #+#             */
/*   Updated: 2023/01/23 10:17:13 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
 * free memory allocated for data structure,
 * remove it from the garbage collector
 *****************************************************************************/

void	free_data(t_data *data)
{
	t_garbage	*tmp;

	tmp = garbage_collector_add(NULL);
	gc_remove(&tmp, data->line);
	gc_remove(&tmp, data->status);
	gc_remove(&tmp, data);
	if (data->line)
		free(data->line);
	if (data->status)
		free(data->status);
	if (data->root)
		del_ast(data->root);
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
	new_env = (char **)malloc(sizeof(char *) * (count_env(&env) + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/******************************************************************************
 * free memory allocated for environment array
 *****************************************************************************/

void	free_env(char ***env)
{
	int		i;
	char	**tmp_env;

	i = 0;
	tmp_env = *env;
	while (*(tmp_env + i))
	{
		free(*(tmp_env + i));
		*(tmp_env + i) = NULL;
		i++;
	}
	free(tmp_env);
	*env = NULL;
}
