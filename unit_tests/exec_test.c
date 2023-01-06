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

START_TEST(test_set_env)
{
	char	*result;
	extern char **environ;
	char **new_env;

	new_env = create_env(environ);
	set_env(&new_env,"TEST","test");
	result = get_env("TEST",new_env);
	ck_assert_int_eq(strcmp(result,"test"),0);
	ck_assert_ptr_nonnull(result);
	set_env(&new_env, "TEST","test2");
	result = get_env("TEST",new_env);
	ck_assert_int_eq(strcmp(result,"test2"),0);
	ck_assert_ptr_nonnull(result);
	set_env(&new_env, "PATH","/bin");
	ck_assert_int_eq(strcmp(get_env("PATH",new_env),"/bin"),0);
	ck_assert_ptr_nonnull(result);
} END_TEST

Suite *exec_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("exec_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_get_path);
	tcase_add_test(tc_core,test_find_binary);
	tcase_add_test(tc_core,test_set_env);
	suite_add_tcase(s, tc_core);
	return (s);
}

int main(void)
{
	int		n_failed;
	Suite	*s;
	SRunner	*sr;

	n_failed = 0;
	s = exec_test();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	n_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (n_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}