/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:53:52 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 15:53:55 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/minishell.h"
#include "../src/exec.h"
#include "check.h"

START_TEST(test_set_env)
{
	char	*result;
	extern char **environ;
	char **new_env;
	int argc;
	char **argv;

	argc = 0;
	argv = NULL;
	new_env = create_env(environ,argc,argv);
	set_env(&new_env,"TEST","test");
	result = get_env("TEST",&new_env);
	ck_assert_int_eq(strcmp(result,"test"),0);
	ck_assert_ptr_nonnull(result);
	set_env(&new_env, "TEST","test2");
	result = get_env("TEST",&new_env);
	ck_assert_int_eq(strcmp(result,"test2"),0);
	ck_assert_ptr_nonnull(result);
	set_env(&new_env, "PATH","/bin");
	ck_assert_int_eq(strcmp(get_env("PATH",&new_env),"/bin"),0);
	ck_assert_ptr_nonnull(result);
} END_TEST

START_TEST(test_get_env)
{
	char	*result;
	extern char **environ;
	char **new_env;
	int argc;
	char **argv;

	argc = 0;
	argv = NULL;
	new_env = create_env(environ,argc,argv);
	result = get_env("PATH",&new_env);
	ck_assert_int_eq(strcmp(result, getenv("PATH")),0);
	ck_assert_ptr_nonnull(result);
	result = get_env("PWD",&new_env);
	ck_assert_int_eq(strcmp(result, getcwd(NULL,0)),0);
	ck_assert_ptr_nonnull(result);
	result = get_env("HOME",&new_env);
	ck_assert_int_eq(strcmp(result, getenv("HOME")),0);
	ck_assert_ptr_nonnull(result);
	result = get_env("TEST",&new_env);
	ck_assert_ptr_null(result);
} END_TEST

Suite *environ_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("environ_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core,test_set_env);
	tcase_add_test(tc_core,test_get_env);
	suite_add_tcase(s, tc_core);
	return (s);
}