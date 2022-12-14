#include "minishell.h"
#include <string.h>


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
	And its tokens from the start each on the new line

	lexer_test just read file, creates t_data struct, then launch lexer() func from project
	And then compare tokens from file with tokens lexer() func putted in data struct.
	 

*/
static void	lexer_test(char *filepath, int num)
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
		printf("No such filepath\n");
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
		printf("Failure while getline() (getline returns \"-1\")\n");
		return ;
	}
	data->line = cmd_line;
	parsed_line = (char **)malloc(sizeof(char *));
	while (i < 20)
	{
		parsed_line[i] = (char *)malloc(sizeof(char) * 100);
		i++;
	}
	i = 0;
	while ((read = getline(&parsed_line[counter], &len, fp)) != -1)
		counter++;
	lexer(data);
	printf("=============> LEXER TEST%d <=============\n", num);
	if (counter == count_token(data->start_token))
		printf("OK - Token count\n");
	else
	{
		printf("[ERROR] Token count!!!\n");
		printf("Given token count - %d\n", counter);
		printf("Lexer token count - %d\n", count_token(data->start_token));
	}
	while (i < counter)
	{
		if (strcmp(parsed_line[i], data->start_token->value))
		{
			printf("Given token value - [%s] : ", parsed_line[i]);
			printf("[%s] - Lexer token value \n", data->start_token->value);
			mistake_flag++;
		}
		data->start_token = data->start_token->next_token;
		i++;
	}
	if (mistake_flag)
		printf("[ERROR] Mistakes in lexer - %d!!!\n", mistake_flag);
	else
		printf("OK - Tokens\n");
	printf("\n");
	free_all(data);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;

	lexer_test("test1.txt", 1);
	return (0);
}
