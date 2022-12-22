/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:09:16 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/22 13:09:41 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"


char	**get_path()
{
	char	*env_path;
	char	**path_array;

	env_path = getenv("PATH");
	path_array = ft_split(env_path,':');
	return (path_array);
}

char 	*find_binary(char *name)
{
	char			**path;
	struct dirent	*entry;
	DIR				*dp;
	int				i,result;
	char			*final_path;
	i = 0;
	path = get_path();
	while (path[i] != 0)
	{
		dp = opendir(path[i]);
		if (dp != NULL)
		{
			entry = readdir(dp);
			while (entry)
			{
				result = ft_strncmp(name,entry->d_name, strlen(name)+1);
				if (result == 0) { // TODO Refactor to prevent leak on the double join
					final_path =ft_strjoin(ft_strjoin(path[i],"/"),name);
					if (access(final_path,X_OK) != -1)
						return (final_path);
					else
						return (NULL);
				}
				entry = readdir(dp);
			}
		}
		closedir(dp);
		i ++;
	}
	return (NULL);
}

char **get_args(t_ast *command_node)
{
	char	**argv;
	int		argc;
	int		i;
	t_ast	*cursor;

	if (command_node == NULL || command_node->type != E_COMMAND
		||command_node->right==NULL)
		return (NULL);
	argc = 0;
	cursor = command_node->right;
	while(cursor)
	{
		argc ++;
		cursor = cursor->left;
	}
	argv = malloc(sizeof(char *)*(argc + 1));
	if (argv == NULL)
		return (NULL);
	if (argc == 1) {
		argv[0] = malloc(sizeof(char));
		argv[0][0] = 0;
		return (argv);
	}
	i = 0;
	cursor = command_node->right;
	while (i < argc)
	{
//		argv[i] = malloc(sizeof(char) * strlen(cursor->token_node->value));
//		if (argv[i] == NULL)
//			return NULL;
		argv[i] = cursor->token_node->value;
		cursor = cursor->left;
		i++;
	}
	argv[i] = 0;
	return (argv);
}

int	runner(t_data *data,char **env)
{
	char	*full_path;
	char	**args;
	int		pid;
	int 	*wstat;

	if (data->root->type == E_COMMAND) {
		full_path = find_binary(data->root->token_node->value);
		args = get_args(data->root);
		pid = fork();
		if (pid == 0)
		{
			printf("\n\n================child here===============\n\n");
			execve(full_path, args, env);


		}
		else if (pid > 0)
		{
			waitpid(pid,wstat,0);
			printf("\n\n================END OF CHILD===============\n\n");
		}
		else
			printf("fork error\n");
	}
}