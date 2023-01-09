#include "check.h"
#include "../src/minishell.h"

START_TEST(test_word) {
	t_data test;

	test.line = "word";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"word"));
	ck_assert_int_eq(E_WORD,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_squote) {
	t_data test;

	test.line = "'";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"'"));
	ck_assert_int_eq(E_SINGLE_QUOTE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_pipe) {
	t_data test;

	test.line = "|";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"|"));
	ck_assert_int_eq(E_PIPE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_dquote) {
	t_data test;

	test.line = "\"";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"\""));
	ck_assert_int_eq(E_DOULE_QUOTE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_empty) {
	t_data test;

	test.line = "";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(1, count_token(test.start_token));
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->token_type);
} END_TEST

START_TEST(test_append) {
	t_data test;

	test.line = ">>";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,">>"));
	ck_assert_int_eq(E_APPEND,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_heredoc) {
	t_data test;

	test.line = "<<";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"<<"));
	ck_assert_int_eq(E_HEREDOC,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST
START_TEST(test_infile) {
	t_data test;

	test.line = "<";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"<"));
	ck_assert_int_eq(E_INFILE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_outfile) {
	t_data test;

	test.line = ">";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,">"));
	ck_assert_int_eq(E_OUTFILE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_multiple_greater_than) {
	t_data test;

	test.line = ">>>>>";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(4, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,">>"));
	ck_assert_int_eq(E_APPEND,test.start_token->token_type);
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->value,">>"));
	ck_assert_int_eq(E_APPEND,test.start_token->next_token->token_type);
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->value,">"));
	ck_assert_int_eq(E_OUTFILE,test.start_token->next_token->next_token->token_type);
} END_TEST

START_TEST(test_separtor) {
	t_data test;

	test.line = "word\nword2\tword3            word4<word5'word6";
	test.start_token = NULL;
	lexer(&test);
	ck_assert_int_eq(9, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"word"));
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->value,"word2"));
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->value,"word3"));
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->next_token->value,"word4"));
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->next_token->next_token->value,"<"));
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->next_token->next_token->next_token->value,"word5"));
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->next_token->next_token->next_token->next_token->value,"'"));
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->next_token->next_token->next_token->next_token->next_token->value,"word6"));
} END_TEST
//TODO : handling quoted string adequately
START_TEST(test_quoted_string) {
	t_data test;
// TODO
	test.line = "\"test  test\"";
	test.start_token = NULL;
	lexer(&test);
//	ck_assert_int_eq(4, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"\""));
	ck_assert_int_eq(E_DOULE_QUOTE,test.start_token->token_type);
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->value,"test  test"));
	ck_assert_int_eq(E_WORD,test.start_token->next_token->token_type);
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->value,"\""));
	ck_assert_int_eq(E_DOULE_QUOTE,test.start_token->next_token->next_token->token_type);
} END_TEST


Suite *lexer_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("data_structures_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_word);
	tcase_add_test(tc_core, test_squote);
	tcase_add_test(tc_core, test_pipe);
	tcase_add_test(tc_core, test_dquote);
	tcase_add_test(tc_core, test_empty);
	tcase_add_test(tc_core, test_append);
	tcase_add_test(tc_core,test_heredoc);
	tcase_add_test(tc_core,test_infile);
	tcase_add_test(tc_core,test_outfile);
	tcase_add_test(tc_core,test_multiple_greater_than);
	tcase_add_test(tc_core,test_separtor);
	tcase_add_test(tc_core,test_quoted_string);
	suite_add_tcase(s, tc_core);
	return (s);
}

//int main(void)
//{
//	int		n_failed;
//	Suite	*s;
//	SRunner	*sr;
//
//	n_failed = 0;
//	s = lexer_test();
//	sr = srunner_create(s);
//	srunner_run_all(sr, CK_VERBOSE);
//	n_failed = srunner_ntests_failed(sr);
//	srunner_free(sr);
//	return (n_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
//}