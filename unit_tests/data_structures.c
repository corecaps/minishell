/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:53:37 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 15:53:39 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include "../src/minishell.h"


START_TEST(test_stack)
{
	t_stack *head;
	int i;

	head = push(E_COMMAND_LINE,NULL);
	ck_assert_ptr_nonnull(head);
	ck_assert_int_eq(head->type,E_COMMAND_LINE);
	head = push(E_COMMAND,head);
	ck_assert_ptr_nonnull(head);
	ck_assert_ptr_nonnull(head->next);
	ck_assert_ptr_null(head->next->next);
	ck_assert_int_eq(head->type,E_COMMAND);
	head = push(E_COMMAND_ARG,head);
	ck_assert_ptr_nonnull(head);
	ck_assert_ptr_nonnull(head->next);
	ck_assert_ptr_nonnull(head->next->next);
	ck_assert_ptr_null(head->next->next->next);
	ck_assert_int_eq(E_COMMAND_ARG,head->type);
	ck_assert_int_eq(E_COMMAND,head->next->type);
	ck_assert_int_eq(E_COMMAND_LINE,head->next->next->type);
	ck_assert_int_eq(pop(&head),E_COMMAND_ARG);
	ck_assert_int_eq(pop(&head),E_COMMAND);
	ck_assert_int_eq(pop(&head),E_COMMAND_LINE);
	ck_assert_int_eq(pop(&head),E_END_OF_TOKEN);
	i = 0;
	while (i++ < 20)
		head = push(i,head);
	ck_assert_int_eq(peek(head),20);
	del_stack(head);
}END_TEST

START_TEST(test_del_ast)
{
	t_ast	*node;
	t_data	*data;
	char	*value;
	int		i;

	i = 0;
	data = (t_data *)malloc(sizeof(t_data));
	node = NULL;
	data->start_token = NULL;
	value = "test";
	add_token(data, E_WORD, value);
	while (i++ < 100)
	{
		node = add_left(node, data->start_token);
		if (node->parent)
			add_right(node->parent, data->start_token);
	}
	del_ast(get_top(node));
	free(node);
	ck_assert_int_eq(1, 1);
}END_TEST

START_TEST(test_add_left)
{
	t_data	*data;
	t_data	*data2;
	t_ast	*top;
	t_ast	*second_node;
	char	*value;
	char	*value2;

	data = (t_data *)malloc(sizeof(t_data));
	data->start_token = NULL;
	data2 = (t_data *)malloc(sizeof(t_data));
	data2->start_token = NULL;
	value = "top";
	value2 = "left child";
	add_token(data, E_WORD, value);
	add_token(data2, E_WORD, value2);
	top = add_left(NULL, data->start_token);
	ck_assert_str_eq(data->start_token->value, top->token_node->value);
	second_node = add_left(top, data2->start_token);
	ck_assert_str_eq(second_node->token_node->value, value2);
	ck_assert_ptr_eq(second_node->parent, top);
	ck_assert_ptr_eq(top->left, second_node);
	free(data->start_token);
	free(data);
	free(data2->start_token);
	free(data2);
	free(second_node);
	free(top);
}END_TEST


START_TEST(test_add_right)
{
	t_ast	*top;
	t_ast	*second_node;
	t_data	*data;
	t_data	*data2;
	char	*value;
	char	*value2;

	data = (t_data *)malloc(sizeof(t_data));
	data->start_token = NULL;
	data2 = (t_data *)malloc(sizeof(t_data));
	data2->start_token = NULL;
	top = NULL;
	value = "top";
	value2 = "right child";
	add_token(data, E_WORD, value);
	add_token(data2, E_WORD, value2);
	top = add_left(NULL, data->start_token);
	ck_assert_str_eq(data->start_token->value, top->token_node->value);
	second_node = add_right(top, data2->start_token);
	ck_assert_str_eq(second_node->token_node->value, value2);
	ck_assert_ptr_eq(second_node->parent, top);
	ck_assert_ptr_eq(top->right, second_node);
	free(data->start_token);
	free(data);
	free(data2->start_token);
	free(data2);
	free(second_node);
	free(top);
}END_TEST

START_TEST(test_add_token)
{
	t_data	*data;
	char	*value1;
	char	*value2;

	data = (t_data *)malloc(sizeof(t_data));
	data->start_token = NULL;
	value1 = "test";
	value2 = "test2";
	add_token(data, E_WORD, value1);
	ck_assert_ptr_nonnull(data->start_token);
	ck_assert_str_eq(data->start_token->value, value1);
	ck_assert_int_eq(data->start_token->token_type, E_WORD);
	add_token(data, E_WORD, value2);
	ck_assert_ptr_nonnull(data->start_token);
	ck_assert_ptr_nonnull(data->start_token->next_token);
	ck_assert_str_eq(data->start_token->value, value1);
	ck_assert_int_eq(data->start_token->token_type, E_WORD);
	ck_assert_str_eq(data->start_token->next_token->value, value2);
	ck_assert_int_eq(data->start_token->next_token->token_type, E_WORD);
	free(data->start_token->next_token);
	free(data->start_token);
	//
	// data->start_token = NULL;
	// add_token(data, E_WORD, NULL);
	// ck_assert_ptr_null(data->start_token);
	// add_token(data, 255, value1);
	// ck_assert_ptr_null(data->start_token);
	// add_token(data, -10, value1);
	// ck_assert_ptr_null(head);
} END_TEST

START_TEST(test_count_token) {
	t_data	*data;
	int		result;
	char	*value1;
	int		i;

	value1 = "test";
	data = (t_data *)malloc(sizeof(t_data));
	data->start_token = NULL;
	result = 0;
	result = count_token(data->start_token);
	ck_assert_int_eq(result, 0);
	i = 0;
	while (i++ < 100)
		add_token(data, E_WORD, value1);
	result = count_token(data->start_token);
	ck_assert_int_eq(result, 100);
	// del_token_list(data->start_token);
	// free(data);
}END_TEST

Suite *data_structures_test(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("data_structures_test");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_add_token);
	tcase_add_test(tc_core, test_count_token);
	tcase_add_test(tc_core, test_add_left);
	tcase_add_test(tc_core, test_add_right);
	tcase_add_test_raise_signal(tc_core, test_del_ast, 6); 	// - ok
	tcase_add_test(tc_core, test_stack);					// - ok
	suite_add_tcase(s, tc_core);
	return (s);
}
