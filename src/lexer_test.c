/* 
	I'M SORRY FOR BAD CODING STILE IN ADVANCE HE HE ))
	lexer_test() - func to test lexer. 
	It gets 2 args:
		* filepath - path to file, which contains command line on first string and tokens on each new line
		* num - number of test, puts manually
	
	Example of testfile:
	
		ls -la | grep -p 
		ls
		-la
		|
		grep
		-p
	
	Where is command line: ls -la | grep -p 
	And its tokens are from the start each on the new line

	lexer_test just read file, creates t_data struct, then launch lexer() func from project
	And then compare tokens from file with tokens lexer() func putted in data struct.
	 

*/

#include "minishell.h"
#include <string.h>

static void	lexer_test(char *filepath)
{
	FILE	*fp;
	t_data	*data;
	char	*cmd_line;
	char	**parsed_line;
	size_t	len;
    ssize_t	read;
	int		counter;
	int		i;
	int		mistake_flag;

	i = 0;
	len = 0;
	counter = 0;
	mistake_flag = 0;
	cmd_line = NULL;
	data = data_init();
	if (!filepath)
	{
		printf("Filepath = NULL\n");
		return ;
	}
	fp = fopen(filepath, "r");
	if (fp == NULL)
	{
		printf("Failure while opening file :[%s]\n", filepath);
		return ;
	}
	if ((read = getline(&cmd_line, &len, fp)) == -1)
	{
		printf("Failure while getline(): getline returns \"-1\" - [%s]\n", filepath);
		return ;
	}
	data->line = cmd_line;
	parsed_line = (char **)malloc(sizeof(char *) * 20);
	while (i < 20)
	{
		parsed_line[i] = (char *)malloc(sizeof(char) * 100);
		i++;
	}
	while ((read = getline(&parsed_line[counter], &len, fp)) != -1)
		counter++;
	lexer(data);
	i = 0;
	while (i < counter)
	{
		if (strncmp(parsed_line[i], data->start_token->value, ft_strlen(data->start_token->value)))
		{
			printf("Given token value - [%s] : ", parsed_line[i]);
			printf("[%s] - Lexer token value in [%s]\n", data->start_token->value, filepath);
			mistake_flag++;
		}
		data->start_token = data->start_token->next_token;
		i++;
	}
	if (mistake_flag)
		printf("[ERROR] Mistakes in lexer - %d in [%s]!!!\n", mistake_flag, filepath);
	else
		printf("OK - [%s]\n", filepath);
	i = 0;
	free_all(data);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	printf("=============> LEXER TEST <=============\n\n");
	lexer_test("./src/lexer_test/test1.txt");
	lexer_test("./src/lexer_test/test2.txt");
	lexer_test("./src/lexer_test/test3.txt");
	lexer_test("./src/lexer_test/test4.txt");
	lexer_test("./src/lexer_test/test5.txt");
	lexer_test("./src/lexer_test/test6.txt");
	lexer_test("./src/lexer_test/test7.txt");
	lexer_test("./src/lexer_test/test8.txt");
	lexer_test("./src/lexer_test/test9.txt");
	lexer_test("./src/lexer_test/test10.txt");
	exit(0);
}
