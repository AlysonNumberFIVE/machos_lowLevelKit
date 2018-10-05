#include <stdio.h>

#include "text_mod.h"



char name[] = "\xeb\x19\xb8\x04\x00\x00\x20\xbf\x01\x00\x00\x00\x5e\xba\x0c\x00\x00\x00\x0f\x05\xb8\x01\x00\x00\x00\x0f\x05\xe8\xe0\xff\xff\xff\x48\x65\x6c\x6c\x6f\x20\x77\x6f\x72\x6c\x64\x0a\x00\x00\x00\x00";
#define VSIZE 48









void		patcher(unsigned char *content, size_t size)
{
	struct mach_header_64		*header64;
	struct load_command			*loader;
	uint64_t					i;

	size_t						original_off;
	header64 = (struct mach_header_64 *)content;
	loader = (struct load_command *)&header64[1];
	i = 0;

	/* search and expand the text secton 
	*/
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64 *seg = (struct segment_command_64*)loader;
			if (strcmp(seg->segname, "__TEXT") == 0)
			{
				int k = 0;
				seg->vmsize += VSIZE;
				struct section_64 *sect = (struct section_64 *)&seg[1];	
				if (strcmp(sect->sectname, "__text") == 0)
				{

					original_off = sect->offset;
					sect->flags += VSIZE;
					sect->offset += VSIZE;
					sect->size += VSIZE;
					break ;
				}
			}		
		}
		i++;
		loader = (struct load_command *)((void*)loader + loader->cmdsize);
	}


	/* Update all the sections after it 
	 */

	i = 0;
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			struct section_64			*tmp;
			struct segment_command_64 	*segm = (struct segment_command_64 *)loader;
			struct section_64 			*secti = (struct section_64 *)&segm[1];
			int 						 a = 0;
			while (a < segm->nsects)
			{
				tmp = &secti[a];
				if (tmp->offset > original_off)
				{
					tmp->addr 	+= VSIZE;
					tmp->offset	+= VSIZE;
				}
				a++;
			}
		}
		else if (loader->cmd == LC_SYMTAB)
		{
			struct symtab_command *sym = (struct symtab_command *)loader;
			sym->symoff += VSIZE;
			sym->stroff += VSIZE;
		}
		else if (loader->cmd == LC_DYSYMTAB)
		{
			struct dysymtab_command *dym = (struct dysymtab_command *)loader;
			dym->tocoff += VSIZE;
			dym->modtaboff += VSIZE;
			dym->extrefsymoff += VSIZE;
			dym->indirectsymoff += VSIZE;
			dym->extreloff += VSIZE;
			dym->locreloff += VSIZE;
		}
		i++;
		loader = (struct load_command *)((void *)loader + loader->cmdsize);
	}


	/*write to file */

	FILE *fp = fopen("new_versoion", "ab+");
	fwrite(content, original_off, 1, fp);
	fwrite(name, VSIZE, 1, fp);
	content = content + original_off;
	size -= original_off;
	fwrite(content, size, 1, fp);
	fclose(fp);
	exit(1);
}

int			main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage : %s <file>\n", argv[0]);
		exit(1);
	}
	unsigned char	*content;
	size_t			size;

	/* map file */
	
	map_file(&content, &size, argv[1]);
	printf("here\n");
	patcher(content, size);
}
