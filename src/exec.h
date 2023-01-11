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

int		apply_redirections(t_ast *node);
int		parse_here_doc(t_ast *node);
int		exec_command_node(t_ast *node, char ***env);
char	**get_args(t_ast *command_node);
int		count_args(t_ast *command_node);
char	*find_binary(char *name);
char	**get_path(void);
int		ft_cd(char **args, char ***env);
int		ft_echo(char **args, char ***env);
int		ft_pwd(char **args, char ***env);
int		ft_exit(char **args, char ***env);
int		ft_env(char **args, char ***env);
int		ft_export(char **args, char ***env);
int		ft_unset(char **args, char ***env);
void	del_environ(char ***env);
int		realloc_environ(char ***env, size_t size, size_t index);
int		exec_pipe(t_ast *current_node, char ***env);
char	*check_absolute_relative_path(char *name);
char	*get_full_path(char *name, char **path);
#endif