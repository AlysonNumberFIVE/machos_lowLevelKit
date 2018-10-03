

#include "readmach.h"

void		section_flag_check(uint64_t	flags)
{
	printf("Flags: \n");
	if (flags == SG_HIGHVM)
		printf("\t\tSG_HIGHVM set\n\n");
	if (flags == SG_NORELOC)
		printf("\t\tSG_NORELOC set\n\n");
}

static void	section_info_64(struct segment_command_64 *segment)
{
	printf("Segment name:        \t\t%s\n", segment->segname);
	printf("Virtual mem address: \t\t%llu\n", segment->vmaddr);
	printf("Virtual mem size:    \t\t%llu\n", segment->vmsize);
	printf("File Offset:         \t\t%llu\n", segment->fileoff);
	printf("File Size:           \t\t%llu\n", segment->filesize);
	printf("Max VM protection:   \t\t%d\n", segment->maxprot);
	printf("Initiona protection: \t\t%d\n", segment->initprot);
	printf("Number of sections:  \t\t%d\n", segment->nsects);
	section_flag_check(segment->flags);
	section_list(segment);
}

static void list_64(struct mach_header *header)
{
	struct mach_header_64 		*header64;
	struct load_command			*loader;
	struct segment_command_64	*segs;
	int							linkedit;

	header64 = (struct mach_header_64 *)header;
	loader = (struct load_command *)&header64[1];
	segs = (struct segment_command_64 *)loader;
	linkedit = 1;
	while (linkedit)
	{
		section_info_64(segs);
		if (strcmp(segs->segname, "__LINKEDIT") == 0)
		{
			linkedit = 0;
		}
		segs = (struct segment_command_64 *)((void *)segs +
			(sizeof(struct segment_command_64) + 
			(sizeof(struct section_64) * segs->nsects)));
	}
}


void		segment_command_list(unsigned char *content)
{
	struct mach_header	*header;

	header = (struct mach_header *)content;
	if (header->filetype != MH_EXECUTE)
	{
		printf("Object files not supported for segment lookup\n");
		exit(1);
	}
	if (is_32_or_64(header) == 64)
		list_64(header);
	else
		printf("32-bit support to work on later\n");
}
