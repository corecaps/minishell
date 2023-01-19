/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:54:16 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/19 12:54:28 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_return_code(char ***env)
{
	char	*return_code;
	char	*open;
	char	*close;
	char	*tmp;

	return_code = get_env("?", env);
	if (!return_code)
		return (NULL);
	if (ft_atoi(return_code) == 0)
	{
		open = ft_strdup("[\033[32m");
		free(return_code);
		return_code = ft_strdup("✓");
		close = ft_strdup("\033[0m]");
	}
	else
	{
		open = ft_strdup("[\033[31m");
		close = ft_strdup("\033[0m]");
	}
	tmp = ft_strjoin(open, return_code);
	free(open);
	open = ft_strjoin(tmp, close);
	free(tmp);
	free(close);
	free(return_code);
	return (open);
}

char *get_user(char ***env)
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
char *get_prompt(char ***env)
{
	char *prompt;
	char *tmp;
	char *tmp2;

	prompt = ft_strdup("\033[0;32m[minishell]");
	if (get_return_code(env))
	{
		tmp = ft_strjoin(get_return_code(env),prompt);
		free(prompt);
		prompt = ft_strdup(tmp);
		free(tmp);
	}
	if (get_user(env))
	{
		tmp = ft_strjoin(prompt,get_user(env));
		free(prompt);
		prompt = ft_strdup(tmp);
		free(tmp);
	}
	tmp = ft_strjoin(prompt, getcwd(NULL, 0));
	tmp2 = ft_strjoin(tmp, "$\033[0m ");
	free(tmp);
	free(prompt);
	return (tmp2);
}