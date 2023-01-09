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

	result = find_binary("ls");
	ck_assert_int_eq(strcmp(result,"/usr/bin/ls"),0);
	ck_assert_ptr_nonnull(result);
	result = find_binary("cat");
	ck_assert_int_eq(strcmp(result,"/usr/bin/cat"),0);
	ck_assert_ptr_nonnull(result);
	result = find_binary("i_do_not_exist");
	ck_assert_ptr_null(result);
} END_TEST



Suite *exec_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("exec_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_get_path);
	tcase_add_test(tc_core,test_find_binary);
	suite_add_tcase(s, tc_core);
	return (s);
}
