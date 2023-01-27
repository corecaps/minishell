#include "../src/minishell.h"
#include "../src/exec.h"

int	main(int argc, char **argv,char **env)
{
	(void)argc;
	(void)argv;

	char	***envp = gc_env_alloc(10);
	(*envp)[0] = ft_strdup("1");
	(*envp)[1]= ft_strjoin("2", "3");
	(*envp)[2] = ft_strdup("4");
	(*envp)[3] = ft_strdup("5");
	(*envp)[4] = ft_strdup("6");
	(*envp)[5] = ft_strdup("7");
	(*envp)[6] = ft_strdup("8");
	(*envp)[7] = ft_strdup("9");
	(*envp)[8] = ft_strdup("10");
	(*envp)[9] = NULL;
	gc_env_add((*envp)[0]);
	gc_env_add((*envp)[1]);
	gc_env_add((*envp)[2]);
	gc_env_add((*envp)[3]);
	gc_env_add((*envp)[4]);
	gc_env_add((*envp)[5]);
	gc_env_add((*envp)[6]);
	gc_env_add((*envp)[7]);
	gc_env_del((*envp)[7]);
	(*envp)[7] = ft_strdup("new one\n ");
	printf("(*envp)[7] = %s\n", (*envp)[7]);
	gc_env_add((*envp)[7]);
	gc_env_add((*envp)[8]);
	gc_env_add((*envp)[9]);
	printf("(*envp)[0] = %s\n", (*envp)[0]);
	gc_env_free();
}

