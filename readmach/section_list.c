

#include "readmach.h"

void	print_section(struct section_64 *content)
{
	printf("\t\t| section name :           \t\t%s\n", content->sectname);
	printf("\t\t| virtual address :        \t\t%llu\n", content->addr);
	printf("\t\t| section size :           \t\t%llu\n", content->size);
	printf("\t\t| section offset :         \t\t%u\n", content->offset);
	printf("\t\t| section alignment :      \t\t%u\n", content->align);
	printf("\t\t| relocation offest :      \t\t%u\n", content->reloff);
	printf("\t\t| number of reloc entries: \t\t%u\n", content->reloff);
	/* section for flag values */	
	printf("\t\t| flag value :             \t\t%#x\n", content->flags);
}

void 	arrow(void)
{
	printf("_____________________________");
	printf("\t\n");
	int i = 0;
	while (i < 5)
	{
		printf("\t|\n");
		i++;
	}
	printf("\t-----------|\n");
	printf("\t           |\n");
}

void	section_list(struct segment_command_64 *segment64)
{
	struct section_64 	*sect;
	uint32_t			i;

	sect = (struct section_64 *)&segment64[1];
	i = 0;
	if (segment64->nsects > 0)
		arrow();
	while (i < segment64->nsects)
	{
		printf("\n\t\t------------------------------\n");
		printf("Block Number : %d\n", i);
		print_section(&sect[i]);
		i++;
		printf("\t\t-------------------------------");
		printf("\n\n");
	}
}
