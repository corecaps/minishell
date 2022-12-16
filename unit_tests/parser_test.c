#include "check.h"
#include "../src/minishell.h"

START_TEST(test_parser) {
	t_data test;
	t_token *cursor;
	int result;

	test.line = "ls | cat";
	test.start_token = NULL;
	lexer(&test);
	cursor = test.start_token;
	while (cursor) {
		printf("\n [%s] type:",cursor->value);
		print_debug(cursor->token_type);
		printf("\n");
		cursor = cursor->next_token;
	}
	result = parse(&test);
	printf("%d\n",result);
	ck_assert_int_eq(result,1);
} END_TEST

Suite *parser_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("parser_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_parser);
	suite_add_tcase(s, tc_core);
	return (s);
}

int main(void)
{
	int		n_failed;
	Suite	*s;
	SRunner	*sr;

	n_failed = 0;
	s = parser_test();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	n_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (n_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}