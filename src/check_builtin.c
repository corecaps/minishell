/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:45:21 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/21 02:20:15 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/******************************************************************************
 * Check if the command is a builtin
 * @param cmd String of the command
 * @return pointer to the builtin if it exist, NULL otherwise
 *****************************************************************************/

t_f_builtin	check_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (ft_echo);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (ft_cd);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (ft_pwd);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (ft_export);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (ft_unset);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (ft_env);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit);
	return (NULL);
}
