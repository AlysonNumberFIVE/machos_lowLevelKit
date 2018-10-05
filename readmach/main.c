
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

	/* adding check for flags */

	map_file(&file, &size, argv[1]);

	/* read header */

	read_header(file);

	/* load command list */

	load_command_list(file);

	/* segment command linst */


	segment_command_list(file);

	/* string table list */

	read_string_table((struct mach_header_64*)file);

	return (0);
}
