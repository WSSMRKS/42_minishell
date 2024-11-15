#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strchr(const char *s, int32_t c)
{
	while (*s)
		if (*s++ == (char)c)
			return ((char *)s - 1);
	if (c == 0)
		return ((char *)s);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	if (ft_strchr("this is a string", 'q') == "q"
	printf("{%s}\n", );
	return (0);
}
