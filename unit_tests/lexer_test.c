#include "check.h"
#include "../src/minishell.h"

START_TEST(test_lexer) {
	t_data test;
	t_token *cursor;

	test.line = "ls -test >ici | essai";
	test.start_token = NULL;
	lexer(&test);
	cursor = test.start_token;
	while (cursor) {
		printf("\n [%s] type:%d\n",cursor->value,cursor->token_type);
		cursor = cursor->next_token;
	}
	ck_assert_int_eq(1,1);
} END_TEST

Suite *lexer_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("data_structures_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_lexer);
	suite_add_tcase(s, tc_core);
	return (s);
}

int main(void)
{
	int		n_failed;
	Suite	*s;
	SRunner	*sr;

	n_failed = 0;
	s = lexer_test();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	n_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (n_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}