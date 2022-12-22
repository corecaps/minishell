/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:12:04 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/22 14:10:30 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// May be some memory leaks because of split
// I freed char array pointer but dont know is it right
// Key and Value strings that allocated in ft_split  will free later
static t_env	*get_env_struct(char *str)
{
	t_env	*env_struct;
	char	**splited_str;
	int		eq;

	eq = 0;
	env_struct = (t_env *)malloc(sizeof(t_env));
	splited_str = ft_split(str, '=');
	if (!splited_str)
		exit(10);
	env_struct->key = splited_str[0];
	env_struct->value = splited_str[1];
	free(splited_str);
	return (env_struct);
}

t_env	**get_env_array(char **env)
{
	t_env	**result;
	char	**tmp;
	int		env_count;
	int		i;

	env_count = 0;
	tmp = env;
	i = 0;
	while (*tmp)
	{
		env_count++;
		tmp++;
	}
	tmp = env;
	result = (t_env **)malloc(sizeof(t_env *) * (env_count));
	printf("Envs count is %d\n", env_count);
	while (i < env_count)
	{
		result[i] = get_env_struct(env[i]);
		i++;
	}
	return (result);
}
