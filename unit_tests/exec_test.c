#include "check.h"
#include "../src/minishell.h"

START_TEST(test_get_path)
{
	char **path;
	int pos;

	path = get_path();
	pos = 0;
	while (path[pos] != 0)
	{
		printf("[%d]-[%s]\n",pos,path[pos]);
		pos ++;
	}
	ck_assert_int_eq(1,1);
} END_TEST

START_TEST(test_find_binary)
{
	char	*result;

	result = find_binary("ls");
	if (result)
		printf("%s\n",result);
	else
		printf("binary not found\n");
	ck_assert_int_eq(1,1);
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