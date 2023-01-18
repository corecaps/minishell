/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:08:09 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 18:16:36 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec
{
	int		*pipes;
	int		pipe_i;
	char	**envp;
	int 	n_child;
	t_ast	*current_node;
	t_ast	*root;
} t_exec;

int			single_cmd(t_exec *exec, char ***env);
int			exec_heredoc(t_exec *exec);
int			exec_leaf(t_exec *exec, int to_close);
void		apply_dup(int fd1, int fd2);
int			run_builtin(t_exec *exec, t_f_builtin builtin);
int			run_leaf(t_exec *exec, int to_close);
int			traverse_pipe(t_exec *exec);
int			apply_redirections(t_ast *node);
int			parse_here_doc(t_ast *node);
char		**get_args(t_ast *command_node);
char		*find_binary(char *name);
char		**get_path(void);
int			ft_cd(char **args, char ***env);
int			ft_echo(char **args, char ***env);
int			ft_pwd(char **args, char ***env);
int			ft_exit(char **args, char ***env);
int			ft_env(char **args, char ***env);
int			ft_export(char **args, char ***env);
int			ft_unset(char **args, char ***env);
void		del_environ(char ***env);
int			realloc_environ(char ***env, size_t size, size_t index);
char		*check_absolute_relative_path(char *name);
char		*get_full_path(char *name, char **path);
int			check_heredoc_last_in(t_ast *current_node);
t_f_builtin	check_builtins(char *cmd);
int			open_redir(char *path,int oflags, t_ast * node,int dest);
void		free_exec(t_exec *exec);
#endif