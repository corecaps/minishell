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
#include <errno.h>
#include <fcntl.h>

//TODO: exec function
//TODO: redirection handling function
// TODO move to path_expander.c
char	**get_path()
{
	char	*env_path;
	char	**path_array;

	env_path = getenv("PATH");
	path_array = ft_split(env_path,':');
	return (path_array);
}
//TODO: move to path_expander.c
char 	*find_binary(char *name)
{
	char			**path;
	struct dirent	*entry;
	DIR				*dp;
	int				i,result;
	char			*final_path;

	// TODO handle relative path
	// TODO extract methods
	// TODO norm
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
// TODO move to arguments.c
static int count_args(t_ast *command_node)
{
	int argc;
	t_ast *cursor;

	argc = 0;
	cursor = command_node->right;
	while(cursor)
	{
		argc ++;
		cursor = cursor->left;
	}
	return argc;
}
// TODO move to arguments.c
char **get_args(t_ast *command_node)
{
	char	**argv;
	int		argc;
	int		i;
	t_ast	*cursor;

	if (command_node == NULL || command_node->type != E_COMMAND )
		return (NULL);
	argc = count_args(command_node);
	argv = malloc(sizeof(char *)*(argc + 2));
	if (argv == NULL)
		return (NULL);
	argv[0] = command_node->token_node->value;
	i = 0;
	cursor = command_node->right;
	while (i < argc)
	{
		argv[i+1] = cursor->token_node->value;
		cursor = cursor->left;
		i++;
	}
	argv[i+1] = 0;
	return (argv);
}

int exec_command_node(t_ast *node, char **env)
{
	char	*full_path;
	char	**args;

	full_path = find_binary(node->token_node->value);
	if (!full_path)
	{
		perror("command not found\n");
		return (-1);
	}
	args = get_args(node);
	if (node->in_pipe > -1)
	{
		dup2(node->in_pipe,STDIN_FILENO);
		close(node->in_pipe);
	}
	if (node->out_pipe > -1)
	{
		dup2(node->out_pipe,STDOUT_FILENO);
		close(node->out_pipe);
	}
	if (node->left)
	{
		printf("Redirecting stdin to %s\n",node->left->token_node->next_token->value);
		if (apply_redirections(node->left) == -1)
			return (-2);
	}
		// TODO : handle heredoc
	execve(full_path, args, env);
	return (0);
}

int apply_redirections(t_ast *node)
{
	int fd;
	if (node->type == E_REDIRECTION && strcmp(node->token_node->value,"<<") != 0)
	{
		if (strcmp(node->token_node->value, "<") == 0)
		{
			fd = open(node->token_node->next_token->value, O_RDONLY);
			if (fd == -1)
				return (-1);//break execution
			else
			{
				dup2(fd,STDIN_FILENO);
				close(fd);
			}
		}
		else if (strcmp(node->token_node->value, ">") == 0)
		{
			fd = open(node->token_node->next_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd,STDOUT_FILENO);
			close(fd);
		}
		else if (strcmp(node->token_node->value, ">>") == 0)
		{
			fd = open(node->token_node->next_token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd,STDOUT_FILENO);
			close(fd);
		}
	}
	if (node->left)
		if (apply_redirections(node->left) == -1)
			return (-1);
	if (node->right)
		if (apply_redirections(node->right) == -1)
			return (-1);
}

int traverse_ast(t_ast *current_node, char **env)
{
	int	status;
	int	pipe_fd[2];
	int	pid;

	if (current_node->type == E_COMMAND)
		return (exec_command_node(current_node, env));
	else if (current_node->type == E_PIPE)
	{
		status = pipe(pipe_fd);
		if (status  < 0)
		{
			perror("pipe error\n");
			return (-2);
		}
		pid = fork();
		if (pid < 0)
		{
			return (-3);
		}
		else if (pid == 0)
		{
			close(pipe_fd[0]);
			current_node->left->out_pipe = pipe_fd[1];
			if (traverse_ast(current_node->left, env) < 0)
				return (-4);
			close (pipe_fd[1]);
		}
		else
		{

			close(pipe_fd[1]);
			if (current_node->right->type == E_COMMAND)
				current_node->right->in_pipe = pipe_fd[0];
			else
				current_node->right->left->in_pipe = pipe_fd[0];
			if (traverse_ast(current_node->right, env) < 0)
				return (-4);
			close(pipe_fd[0]);
			status = waitpid(pid,&status,0);
			if (status != 0)
				return (status);
		}
	}
	return (0);
}