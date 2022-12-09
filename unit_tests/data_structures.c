#include "check.h"
#include "../src/minishell.h"

START_TEST(test_add_token)
{
	t_token *head;
	char *value1;
	char *value2;

	head = NULL;
	value1 = "test";
	value2 = "test2";
	head = add_token(head,E_WORD,value1);
	ck_assert_ptr_nonnull(head);
	ck_assert_str_eq(head->value,value1);
	ck_assert_int_eq(head->token_type,E_WORD);
	head = add_token(head,E_WORD,value2);
	ck_assert_ptr_nonnull(head);
	ck_assert_ptr_nonnull(head->next_token);
	ck_assert_str_eq(head->value,value1);
	ck_assert_int_eq(head->token_type,E_WORD);
	ck_assert_str_eq(head->next_token->value,value2);
	ck_assert_int_eq(head->next_token->token_type,E_WORD);
	free(head->next_token);
	free(head);
	head = NULL;
	head = add_token(head,E_WORD,NULL);
	ck_assert_ptr_null(head);
	head = add_token(head,255,value1);
	ck_assert_ptr_null(head);
	head = add_token(head,-10,value1);
	ck_assert_ptr_null(head);
} END_TEST

START_TEST(test_count_token) {
	t_token *head;
	int result;
	char *value1;
	int i;

	value1 = "test";
	head = NULL;
	result = 0;
	result = count_token(head);
	ck_assert_int_eq(result,0);
	i=0;
	while (i++ < 100)
		head = add_token(head,E_WORD,value1);
	result = count_token(head);
	ck_assert_int_eq(result,100);
	del_token_list(head);
}END_TEST

Suite *data_structures_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("data_structures_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_add_token);
	tcase_add_test(tc_core, test_count_token);
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