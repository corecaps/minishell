/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:54:11 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 15:54:13 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "../src/minishell.h"
extern char **environ;

START_TEST(test_word) {
	t_data test;
	char **new_env;
	test.line = "word";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"word"));
	ck_assert_int_eq(E_WORD,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_squote) {
	t_data test;
	char **new_env;
	test.line = "'";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"'"));
	ck_assert_int_eq(E_SINGLE_QUOTE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_pipe) {
	t_data test;
	char **new_env;

	test.line = "|";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"|"));
	ck_assert_int_eq(E_PIPE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_dquote) {
	t_data test;
	char **new_env;

	test.line = "\"";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"\""));
	ck_assert_int_eq(E_DOULE_QUOTE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_empty) {
	t_data test;
	char **new_env;
	test.line = "";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(1, count_token(test.start_token));
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->token_type);
} END_TEST

START_TEST(test_append) {
	t_data test;
	char **new_env;

	test.line = ">>";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,">>"));
	ck_assert_int_eq(E_APPEND,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_heredoc) {
	t_data test;
	char **new_env;

	test.line = "<<";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"<<"));
	ck_assert_int_eq(E_HEREDOC,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST
START_TEST(test_infile) {
	t_data test;
	char **new_env;

	test.line = "<";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"<"));
	ck_assert_int_eq(E_INFILE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_outfile) {
	t_data test;
	char **new_env;

	test.line = ">";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	ck_assert_int_eq(2, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,">"));
	ck_assert_int_eq(E_OUTFILE,test.start_token->token_type);
	ck_assert_int_eq(E_END_OF_TOKEN, test.start_token->next_token->token_type);
} END_TEST

START_TEST(test_multiple_greater_than) {
	t_data test;
	char **new_env;

	test.line = ">>>>>";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
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
	char **new_env;

	test.line = "word\nword2\tword3            word4<word5'word6";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
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

START_TEST(test_quoted_string) {
	t_data test;
	char **new_env;
// TODO : test FAILS with simple quote inside double quotes
	test.line = "\"test  test\"";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
//	ck_assert_int_eq(5, count_token(test.start_token));
	ck_assert_int_eq(0, strcmp(test.start_token->value,"\""));
	ck_assert_int_eq(E_DOULE_QUOTE,test.start_token->token_type);
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->value,"test  test"));
	ck_assert_int_eq(E_WORD,test.start_token->next_token->token_type);
	ck_assert_int_eq(0, strcmp(test.start_token->next_token->next_token->value,"\""));
	ck_assert_int_eq(E_DOULE_QUOTE,test.start_token->next_token->next_token->token_type);
} END_TEST

START_TEST(test_expand_variable) {
	t_data test;
	char *path;
	char **new_env;

	test.line = "$PATH";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	path = getenv("PATH");
	ck_assert_int_eq(strcmp(test.start_token->value, path), 0);
	test.line = "$NOTHING";
	test.start_token = NULL;
	lexer(&test,&new_env);
	ck_assert_int_eq(strcmp(test.start_token->value, ""), 0);
	test.line = "ls $NOTHING";
	test.start_token = NULL;
	lexer(&test,&new_env);
	ck_assert_int_eq(strcmp(test.start_token->value, "ls"), 0);
	ck_assert_int_eq(strcmp(test.start_token->next_token->value, ""), 0);

//******* TODO : Test FAILS
//	test.line = "$PATH$PATH";
//	test.start_token = NULL;
//	lexer(&test);
//	path = ft_strjoin(getenv("PATH"), getenv("PATH"));
//	printf("token : %s\n\n\nvariable : %s\n", test.start_token->value, path);
//	ck_assert_int_eq(strcmp(test.start_token->value, path), 0);
} END_TEST


Suite *lexer_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("lexer_test");
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
	tcase_add_test(tc_core,test_expand_variable);

	suite_add_tcase(s, tc_core);
	return (s);
}