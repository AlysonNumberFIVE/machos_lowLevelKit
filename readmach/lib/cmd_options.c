

#include <ctype.h>
#include "lib.h"

char		*cmd_options(int argc, char **argv)
{
	int		i 		= 1;
	char 	*tmp	= NULL;
	char	*cmd 	= (char *)malloc(sizeof(char));

	while (i < argc)
	{
		if (argv[i][0] != '-' || !isalpha(argv[i][1]))
		{
			free(cmd);
			cmd = NULL;
			break ;
		}
		else
		{
			tmp = join(cmd, &argv[i][1]);
			free(cmd);
			cmd = strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (cmd);
}