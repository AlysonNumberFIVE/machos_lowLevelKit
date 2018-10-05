
#include <fcntl.h>
#include <unistd.h>
#include "block.h"

struct section_64	*forged_block(void);

/*
** Testing forging a block without crashing the binary
*/

uint64_t			size_offset(struct load_command *loader, uint64_t offset)
{
	uint64_t		size = sizeof(struct section_64);

	if (loader->cmd == LC_SEGMENT_64)
	{
		struct segment_command_64 *seg = (struct segment_command_64 *)loader;
		if (seg->fileoff > offset) return (size);
	}
	else if (loader->cmd == LC_SYMTAB)
	{
		struct symtab_command *sym = (struct symtab_command *)loader;
		if (sym->symoff > offset) return (size);
	}
	else if (loader->cmd == LC_DYSYMTAB)
	{
		struct dysymtab_command *dymsym = (struct dysymtab_command *)loader;
		if (dymsym->tocoff > offset) return (size);
	}
	else if (loader->cmd == LC_DATA_IN_CODE ||
	loader->cmd == LC_FUNCTION_STARTS || loader->cmd >= INDIRECT_SYMBOL_LOCAL)
	{
		struct linkedit_data_command *lin = (struct linkedit_data_command *)loader;
		if (lin->dataoff > offset) return (size);
	}
	return (0);
}

/*
** Edit all physical offset 
*/

void				write_file(struct mach_header_64 *header64, size_t size,
		size_t offset_v)
{
	struct section_64	*forgery = forged_block();
	FILE *fp = fopen("Testing", "wb+");
	unsigned char *content;
	unsigned char *temp;
	struct section_64 forge;

	/* forge name */

	memcpy(forge.sectname, "__forged_block_\0", 16);
	memcpy(forge.segname, "__TEXT\0", 7);
	forge.addr = 0;
	forge.size = 0;
	forge.offset = 0;
	forge.align = 0;
	forge.reloff = 0;
	forge.nreloc = 0;
	forge.flags = 0;	

	/* end forge */


	struct segment_command_64 *seg;
	content = (unsigned char *)header64;
	size_t c = fwrite(content, sizeof(struct mach_header_64), 1, fp);
	struct load_command *loader = (struct load_command *)&header64[1];
	uint32_t i = 0;
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)loader;
			if (strcmp(seg->segname, "__TEXT") == 0)
				seg->nsects += 1;
			if (strcmp(seg->segname, "__TEXT") == 0)
			{
				/* plus 1 was added for byte alignment: 
				 * This might need to be edited to automate */
				fwrite(seg, (sizeof(struct segment_command_64) +
						sizeof(struct section_64) * seg->nsects - 1), 1, fp);
				fseek(fp, sizeof(struct section_64) * -1 + 1, SEEK_CUR);	
				size_t k = fwrite(forgery, sizeof(struct section_64), 1, fp);
				break ;
			}
			else
				fwrite(seg, (sizeof(struct segment_command_64) + (sizeof(struct section_64) * seg->nsects)), 1, fp);
		}
		if (strcmp(seg->segname, "__TEXT") == 0)
			loader = (struct load_command *)((void*)loader + loader->cmdsize - sizeof(struct section_64));
		else
			loader = (struct load_command*)((void*)loader + loader->cmdsize);
		i++;
	}
	i = 0;
	loader = (struct load_command*)&header64[1];
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)loader;
			printf("segname is : %s\n", seg->segname);
			if (strcmp(seg->segname, "__DATA") == 0)
			{
				break ;
			}
		}
		loader = (struct load_command *)((void*)loader + loader->cmdsize);
		i++;
	}
	size_t q = 0;
	while (q < size)
	{
		if (strcmp(&content[q], "__DATA") == 0)
		{
			seg = (struct segment_command_64 *)&content[q - (sizeof(uint32_t) * 2)];
			printf("data section found\n");
			printf("seg name is %s\n", seg->segname);
			printf("cmdsize -> %u\n", seg->cmdsize);
			printf("offset -> %llu\n", seg->vmaddr);
			printf("size -> %llu\n", seg->vmsize);
			fwrite(seg, (sizeof(struct segment_command_64) + (sizeof(struct section_64) * seg->nsects)), 1, fp);
			break ;
		}
		q++;
	}
	q -= (sizeof(uint32_t) * 2);
	size = size - (q + (sizeof(struct segment_command_64) + (sizeof(struct section_64) *
					seg->nsects)));
	q = q + (sizeof(struct segment_command_64) + (sizeof(struct section_64) * seg->nsects));
	fwrite(&content[q], size, 1, fp);

/*	loader = (struct load_command *)seg;
	while (i < header64->ncmds)
	{
		fwrite(loader, loader->cmdsize, 1, fp);
		i++;
		loader = (struct load_command *)((void*)loader + loader->cmdsize);
	} */
	fclose(fp);
}



void				readjust_offsets(struct mach_header_64 *header64,
		uint64_t offset_v, size_t size)
{
	struct load_command *loader;
	uint64_t			value;
	uint32_t			i;
	int					t_flag = 0;

	loader = (struct load_command *)&header64[1];
	header64->sizeofcmds += sizeof(struct section_64);
	i = 0;
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64 *is_text = (struct segment_command_64 *)loader;
			if (strcmp(is_text->segname, "__TEXT") == 0)
			{
				struct section_64 *t;
				struct section_64 *texter = (struct section_64 *)&is_text[1];
				int k = 0;
				is_text->vmsize += 80;
				while (k < is_text->nsects)
				{
					t = &texter[k];
					t->addr += 80;
					t->offset += 80;
					k++;
				}
				loader = (struct load_command *)((void*)loader + 
						loader->cmdsize - (sizeof(struct section_64)));
				break ;
			}
		}
		loader = (struct load_command *)((void*)loader + loader->cmdsize);
		i++;
	}
	

	while (i < header64->ncmds)
	{
		value = size_offset(loader, offset_v);
		printf("cmd is %#x\n", loader->cmd);
		if (loader->cmd == LC_SEGMENT_64)
		{	
			struct segment_command_64 *seg = (struct segment_command_64 *)loader;
			seg->fileoff += value;
			int j = 0;
			struct section_64 *tmp;
			seg->vmsize += 80;
			struct section_64 *sect = (struct section_64 *)&seg[1];
			while (j < seg->nsects)
			{
				tmp = &sect[j];
				tmp->addr += 80;
				tmp->offset += 80;
				j++;
			}
		}
		else if (loader->cmd == LC_SYMTAB)
		{
			struct symtab_command *sym = (struct symtab_command *)loader;
			printf("SYMOFF += %zu\n", value);
			sym->symoff += value;
			sym->stroff += value;
		}
		else if (loader->cmd == LC_DYSYMTAB)
		{
			printf("DYNSYM : %llu\n", value);
			struct dysymtab_command *dym = (struct dysymtab_command *)loader;
			dym->tocoff += value;
			dym->modtaboff += value;
			dym->extrefsymoff += value;
			dym->indirectsymoff += 80;
			dym->extreloff += value;
			dym->locreloff += value;

		}
		else if (loader->cmd == LC_DATA_IN_CODE ||
			loader->cmd == LC_FUNCTION_STARTS ||
			loader->cmd == INDIRECT_SYMBOL_LOCAL)
		{
			printf("LC_DATA_IN_C\n");
			struct linkedit_data_command *lin = (struct linkedit_data_command *)loader;
			//lin->dataoff += value;
			if (loader->cmd == LC_DATA_IN_CODE)
			{
				struct data_in_code_entry *in_c = (struct data_in_code_entry *)loader;
				//in_c->offset += value;
			}
		}
		loader = (struct load_command *)((void*)loader + loader->cmdsize);
		i++;
	}
	write_file(header64, size, offset_v);
}


/*
** Forged block
*/

struct section_64	*forged_block(void)
{
	struct section_64	*fake;
	char				text[]	= "__TEXT";
	char				faker[]	= "__fake_block__";

	fake = (struct section_64 *)malloc(sizeof(struct section_64));
	bzero(fake->sectname, 16);
	bzero(fake->segname, 16);
	memcpy(fake->segname, text, 6);
	memcpy(fake->sectname,  faker, 14);
	fake->addr 					= 0;
	fake->size 					= 0;
	fake->offset 				= 0;
	fake->align 				= 0;
	fake->reloff				= 0;
	fake->nreloc				= 0;
	fake->flags					= 0;
	return (fake);
}

/*
** Write modified binary. Adjusting offsets before virual addresses.
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
	uint64_t					distance;

	header64 = (struct mach_header_64 *)content;
	loader = (struct load_command *)&header64[1];
	i = 0;
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			search_test = (struct segment_command_64 *)loader;
			if (strcmp(search_segment, search_test->segname) == 0)
			{
				distance = search_test->fileoff;
				search_test->cmdsize += sizeof(struct section_64);
				break ;
			}
		}
		loader = (struct load_command *)((void*)loader + 
				loader->cmdsize);
		i++;
	}
	readjust_offsets(header64, distance, size);
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
