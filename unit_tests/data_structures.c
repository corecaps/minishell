#include "check.h"
#include "../src/minishell.h"

START_TEST(test_stack)
{
	ck_assert_int_eq(1,1);
} END_TEST

Suite *data_structures_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("data_structures_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_stack);
	suite_add_tcase(s, tc_core);
	return s;
}

int main(void)
{
	int n_failed = 0;
	Suite *s;
	SRunner *sr;
	s = data_structures_test();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	n_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (n_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}