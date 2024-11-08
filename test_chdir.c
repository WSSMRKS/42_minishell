#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
	char *path;

	path = malloc(sizeof(char) * (500 + 1));
	printf("%s\n", getcwd(path, 500));
	printf("Return value of chdir: {%d}\n", chdir("./"));
	printf("%s\n", getcwd(path, 500));
	printf("Return value of execve: {%d}\n", execve("../minishell_1st/minishell", argv, envp));
	return (0);
}
