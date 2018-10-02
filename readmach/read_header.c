

#include "readmach.h"

void		assess_filetype(struct mach_header *header)
{
	if (header->filetype == MH_OBJECT)
		printf("Object file\n");
	else if (header->filetype == MH_EXECUTE)
		printf("Executable file\n");
	else if (header->filetype == MH_CORE)
		printf("Core file\n");
}

void		read_header(unsigned char *content)
{
	struct mach_header		*header;

	printf("Header Information ***********************\n");
	header = (struct mach_header *)content;
	printf("\nArchitecture :\t\t\t");
	header->magic == MH_MAGIC ? printf("32-bit\n") : printf("64-bit\n");
	printf("\nFile Endianness :\t\t");
	header->magic == MH_CIGAM ||
	  	header->magic == MH_CIGAM_64 ? printf("Reverse-Endianness\n") :
		printf("Endianness\n");
	printf("\nFiletype :\t\t\t");
	assess_filetype(header);
	printf("\nNumber of Load Commands : \t");
	printf("%d\n", header->ncmds);
	printf("\nSize of all load commands : \t");
	printf("%u\n", header->sizeofcmds);
	printf("\n******************************************\n");
}
