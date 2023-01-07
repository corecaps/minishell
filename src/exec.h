/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:08:09 by jgarcia           #+#    #+#             */
/*   Updated: 2022/12/22 13:09:11 by jgarcia          ###   ########.fr       */
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
char	**get_path();
int		ft_cd(char **args, char **env);
int		ft_echo(char **args, char **env);
int		ft_pwd(char **args,char **env);
void	del_environ(char ***env);
int		realloc_environ(char ***env,size_t size);
int		set_env(char ***env,char *key,char *value);
#endif