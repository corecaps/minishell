#include "check.h"
#include "../libft/libft.h"
#include "../src/minishell.h"
#include "../src/lexer.h"
#include "../src/parser.h"
#include "../src/exec.h"
#include "test.h"


int main(void)
{
	int		n_failed;
	Suite	*s[4];
	SRunner	*sr;

	n_failed = 0;
	s[0] = data_structures_test();
	s[1] = lexer_test();
	s[2] = parser_test();
	s[3] = exec_test();
	sr = srunner_create(s[0]);
	srunner_add_suite(sr,s[1]);
	srunner_add_suite(sr,s[2]);
	srunner_add_suite(sr,s[3]);
	srunner_run_all(sr, CK_VERBOSE);
	n_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (n_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}