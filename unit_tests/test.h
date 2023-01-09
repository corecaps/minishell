/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:54:53 by jgarcia           #+#    #+#             */
/*   Updated: 2023/01/09 15:54:57 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TESTS_TEST_H
#define UNIT_TESTS_TEST_H
#include "check.h"
Suite	*data_structures_test(void);
Suite	*lexer_test(void);
Suite	*parser_test(void);
Suite	*exec_test(void);
Suite	*environ_test(void);
#endif //UNIT_TESTS_TEST_H
