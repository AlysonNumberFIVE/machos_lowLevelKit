
#include "block.h"

/*
** Testing forging a block without crashing the binary
*/


/*
** Forged block
*/

struct section_64	*forged_block(void)
{
	struct section_64	*fake;
	char				text[] = "__TEXT";
	char				faker[] = "__fake_block__";

	fake = (struct section_64 *)malloc(sizeof(struct section_64));
	bzero(fake->sectname, 16);
	bzero(fake->segname, 16);
	memcpy(fake->sectname, text, 6);
	memcpy(fake->segname,  faker, 14);
	fake->addr 			= 0;
	fake->size 			= 0;
	fake->offset 		= 0;
	fake->align 		= 0;
	fake->reloff		= 0;
	fake->nreloc		= 0;
	fake->flags			= 0;
	return (fake);
}

/*
** Write modified binary 
*/

void				write_modified_file(unsigned char *content,
		size_t size, size_t offest, char *search_segment)
{
	struct segment_command_64	*search_test;
	struct mach_header_64		*header64;
	int							fd;
	struct load_command			*loader;
	struct load_command			*temp;
	uint32_t					i;

	//fd = open("test_blocker", O_RDWR | O_CREAT | O_TRUNC, 0744);
	header64 = (struct mach_header_64 *)content;
	loader = (struct load_command *)&header64[1];
	i = 0;
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			search_test = (struct segment_command_64 *)loader;
			if (strcmp(search_segment, search_test->segname) == 0)
				printf("Found\n");
		}
		if (loader->cmd == LC_SYMTAB)
		{
			printf("symtab found\n");
		}
		if (loader->cmd == LC_DYSYMTAB)
		{
			printf("dynamic symtab found\n");
		}
		printf("loadc : %d\n", loader->cmd);
		loader = (struct load_command *)((void*)loader + 
				loader->cmdsize);
		i++;
	}
}	


void				error_and_leave(void)
{
	printf("Segment not found\n");
	exit(1);
}

/*
** Will probably turn this into a standalone function as this loop is 
** used a lot 
*/


uint64_t			does_block_exist(struct mach_header_64 *header64,
		char *to_find)
{
	struct load_command			*loader;
	struct load_command			*temp;
	struct segment_command_64	*segs;
	uint32_t					i;
	int							linkedit;

	loader = (struct load_command *)&header64[1];
	segs = (struct segment_command_64 *)loader;
	linkedit = 1;
	while (linkedit)
	{
		if (strcmp(segs->segname, to_find) == 0)
			return (segs->fileoff);
		if (strcmp(segs->segname, "__LINKEDIT") == 0)
			linkedit = 0;
		segs = (struct segment_command_64 *)((void *)segs +
			(sizeof(struct segment_command_64) +
			(sizeof(struct section_64) * segs->nsects)));
	}
	return (-1);
}

void			block_forge(unsigned char *content, size_t size, 
		char *segment_name)
{
	struct mach_header_64 	*header64;
	uint64_t				file_offset;
	struct section_64		*new_block;

	header64 = (struct mach_header_64 *)content;
	if ((file_offset = does_block_exist(header64, segment_name)) == 1)
		error_and_leave();
	printf("file offset to section is %llu\n", file_offset);
	write_modified_file(content, size, file_offset, segment_name);
}


int				main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Usage : %s [filename]\n", argv[0]);
		exit(1);
	}
	unsigned char	*content;
	size_t			size;
	char			*segment;
		
	/* map file conetent */

	map_file(&content, &size, argv[1]);

	/* target the segment to modify */

	segment = argv[2];

	/* forging block operation */

	block_forge(content, size, segment);

	/* end of test */


}
