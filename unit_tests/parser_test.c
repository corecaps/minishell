/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:54:40 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 15:54:44 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "../src/minishell.h"
extern char **environ;

START_TEST(test_parser) {
	t_data test;
	int result;
	char **new_env;
	test.line = "< test ls arg1 arg2 arg3 < test2 arg4 | cat";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	result = parse(&test);
	ck_assert_int_eq(1, result);
	ck_assert_ptr_nonnull(test.root);
	ck_assert_int_eq(test.root->type, E_PIPE);
	ck_assert_int_eq(test.root->left->type, E_COMMAND);
	ck_assert_int_eq(strcmp(test.root->left->token_node->value, "ls"), 0);
	ck_assert_int_eq(strcmp(test.root->left->left->token_node->value, "<"), 0);
	ck_assert_int_eq(strcmp(test.root->left->left->token_node->next_token->value, "test"), 0);
	ck_assert_int_eq(strcmp(test.root->left->left->left->token_node->value, "<"), 0);
	ck_assert_int_eq(strcmp(test.root->left->left->left->token_node->next_token->value, "test2"), 0);
	ck_assert_int_eq(strcmp(test.root->left->right->token_node->value, "arg1"), 0);
	ck_assert_int_eq(strcmp(test.root->left->right->left->token_node->value, "arg2"), 0);
	ck_assert_int_eq(strcmp(test.root->left->right->left->left->token_node->value, "arg3"), 0);
	ck_assert_int_eq(strcmp(test.root->left->right->left->left->left->token_node->value, "arg4"), 0);
	ck_assert_int_eq(test.root->right->type, E_COMMAND);
	ck_assert_int_eq(strcmp(test.root->right->token_node->value, "cat"), 0);
	ck_assert_ptr_null(test.root->right->left);
	ck_assert_ptr_null(test.root->right->right);
} END_TEST

START_TEST(parser_empty_string)
{
	t_data test;
	int result;
	char **new_env;

	test.line = "";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	result = parse(&test);
	ck_assert_int_eq(1, result);
	ck_assert_ptr_null(test.root);
} END_TEST

START_TEST(parser_only_spaces)
{
	t_data test;
	int result;
	char **new_env;

	test.line = "   ";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	result = parse(&test);
	ck_assert_int_eq(1, result);
	ck_assert_ptr_null(test.root);
} END_TEST

START_TEST(parser_invalid_syntax)
{
	t_data test;
	int result;
	char **new_env;

	test.line = "ls |";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);
	test.line = "ls <";
	test.start_token = NULL;
	lexer(&test,&new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);
	test.line = ">|";
	test.start_token = NULL;
	lexer(&test,&new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);
	test.line = "ls \"haha";
	test.start_token = NULL;
	lexer(&test,&new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);

} END_TEST

START_TEST(parser_invalid_syntax2)
{
	t_data test;
	int result;
	char **new_env;

	test.line = "ls | |";
	test.start_token = NULL;
	new_env = create_env(environ,0,NULL);
	lexer(&test, &new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);
	test.line = "ls < <";
	test.start_token = NULL;
	lexer(&test,&new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);
	test.line = ">| |";
	test.start_token = NULL;
	lexer(&test,&new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);
	test.line = "ls 'haha ";
	test.start_token = NULL;
	lexer(&test,&new_env);
	result = parse(&test);
	ck_assert_int_eq(-2, result);

} END_TEST

Suite *parser_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("parser_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_parser);
	tcase_add_test(tc_core, parser_empty_string);
	tcase_add_test(tc_core, parser_only_spaces);
	tcase_add_test(tc_core, parser_invalid_syntax);
	tcase_add_test(tc_core, parser_invalid_syntax2);
	suite_add_tcase(s, tc_core);
	return (s);
}