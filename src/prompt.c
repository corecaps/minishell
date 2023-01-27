/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:54:16 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/27 17:12:02 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_return_code(char **return_code, char **open, char **close)
{
	if (ft_atoi((*return_code)) == 0)
	{
		(*open) = ft_strdup("[\033[32m");
		free((*return_code));
		(*return_code) = ft_strdup("✓");
		(*close) = ft_strdup("\033[0m]");
	}
	else
	{
		(*open) = ft_strdup("[\033[31m");
		(*close) = ft_strdup("\033[0m]");
	}
}

char	*get_return_code(char ***env)
{
	char	*return_code;
	char	*open;
	char	*close;
	char	*tmp;

	return_code = get_env("?", env);
	if (!return_code)
		return (NULL);
	check_return_code(&return_code, &open, &close);
	tmp = ft_strjoin(open, return_code);
	free(open);
	open = ft_strjoin(tmp, close);
	free(tmp);
	free(close);
	free(return_code);
	return (open);
}

char	*get_user(char ***env)
{
	char	*user;
	char	*tmp;

	user = get_env("USER", env);
	if (!user)
		return (NULL);
	tmp = ft_strjoin(user, "@");
	free(user);
	return (tmp);
}

void	prompt_join(char **prompt, char *tmp, int dir)
{
	char	*tmp2;

	if (dir == 1)
		tmp2 = ft_strjoin(tmp, *prompt);
	else
		tmp2 = ft_strjoin(*prompt, tmp);
	free(*prompt);
	free(tmp);
	*prompt = ft_strdup(tmp2);
	free(tmp2);
}

char	*get_prompt(char ***env)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strdup("\033[0;32m[minishell]");
	tmp = get_return_code(env);
	if (tmp)
		prompt_join(&prompt, tmp, 1);
	tmp = get_user(env);
	if (tmp)
		prompt_join(&prompt, tmp, 2);
	tmp = getcwd(NULL, 0);
	if (tmp)
		prompt_join(&prompt, tmp, 2);
	tmp = ft_strdup("$\033[0m ");
	prompt_join(&prompt, tmp, 2);
	return (prompt);
}
