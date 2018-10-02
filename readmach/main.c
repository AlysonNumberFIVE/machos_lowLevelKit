
#include "readmach.h"

int			main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage : %s [file to examine]\n", argv[0]);
		exit(1);
	}
	unsigned char 	*file;
	size_t			size;

	/* only works with one file currently */

	map_file(&file, &size, argv[1]);
	
	/* read header */

	read_header(file);

	return (0);
}
