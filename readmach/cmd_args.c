
#include <ctype.h>
#include "readmach.h"

char		*cmd_args(int argc, char **argv)
{
	int			i 			= 1;
	char		*arguments 	= NULL;

	while (i < argc)
	{
		if (argv[i][0] == '-' && isalpha(argv[i][1]))
			arguments = charpush(arguments, argv[i][1]);
		i++;
	}
	return (arguments);
}
