/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:54:02 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 15:54:04 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "../src/minishell.h"
#include "../src/exec.h"
#include <string.h>
extern char **environ;
START_TEST(test_get_path)
{
	char **path;
	int pos;

	path = get_path();
	pos = 0;
	ck_assert_ptr_nonnull(path);
	while (path[pos] != 0)
	{
		ck_assert_ptr_nonnull(path[pos]);
		pos ++;
	}
	ck_assert_int_gt(pos,0);
} END_TEST

START_TEST(test_find_binary)
{
	char	*result;

	result = find_binary("ls", NULL);
	ck_assert_int_eq(strcmp(result,"/usr/bin/ls"),0);
	ck_assert_ptr_nonnull(result);
	result = find_binary("cat", NULL);
	ck_assert_int_eq(strcmp(result,"/usr/bin/cat"),0);
	ck_assert_ptr_nonnull(result);
	result = find_binary("i_do_not_exist", NULL);
	ck_assert_ptr_null(result);
} END_TEST

START_TEST(test_traverse_ast)
{
	t_data	test;
	char **new_env;
	int fd;
	char buffer[1024];
	char buffer2[1024];

	bzero(buffer,1024);
	bzero(buffer2,1024);
	test.line = "cat Makefile | cat | wc > test.txt";
	new_env = create_env(environ,0,NULL);
	test.start_token = NULL;
	lexer(&test,&new_env);
	parse(&test);
	exec_cmd_line(test.root, &new_env, NULL);
	system("cat Makefile | cat | wc > test2.txt");
	fd = open("test.txt", O_RDONLY);
	read(fd, buffer, 256);
	close (fd);
	fd = open("test2.txt", O_RDONLY);
	read(fd, buffer2, 256);
	close(fd);
	ck_assert_int_eq(strcmp(buffer,buffer2),0);
} END_TEST

START_TEST(test_traverse_ast_binary_not_found)
{
	t_data	test;
	char **new_env;
	int result;

	test.line = "idonotexist";
	new_env = create_env(environ,0,NULL);
	test.start_token = NULL;
	lexer(&test,&new_env);
	parse(&test);
	result = exec_cmd_line(test.root, &new_env, NULL);

	ck_assert_int_eq(result,3);
} END_TEST

Suite *exec_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("exec_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_get_path);
	tcase_add_test(tc_core,test_find_binary);
	tcase_add_test(tc_core,test_traverse_ast);
	tcase_add_test(tc_core,test_traverse_ast_binary_not_found);
	suite_add_tcase(s, tc_core);
	return (s);
}