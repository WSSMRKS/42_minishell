#include "../../libft/libft.h"

int	main(int argc, char **argv)
{
	int	retval;

	if (argc < 2)
		return (1);
	if (!strsl_atoi(cstr_view(argv[1]), base10(), &retval, OFB_TRUNCATE))
		return (2);
	return (retval);
}
