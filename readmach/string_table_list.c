
#include "readmach.h"

void		print_dysymtab(struct dysymtab_command *dysym)
{
	printf("******************* Dynamic Symbol struct \n");
	printf("Index to local syms:\t        %u\n", dysym->ilocalsym);
	printf("Number of local syms:\t        %u\n", dysym->nlocalsym);
	printf("Indext to external syms:\t%u\n", dysym->iextdefsym);
	printf("Number of external syms:\t   %u\n", dysym->nextdefsym);
	printf("Index of undefined syms:\t   %u\n", dysym->iundefsym);
	printf("Number of undefine syms:\t   %u\n", dysym->nundefsym);
	printf("Offset to table of cont:\t   %u\n", dysym->tocoff);
	printf("Number of table of cont:\t   %u\n", dysym->ntoc);
	printf("Offset to module table:\t    %u\n", dysym->modtaboff);
	printf("Number of mod table entr:\t  %u\n", dysym->nmodtab);
	printf("Offset to referenc symtab:\t %u\n", dysym->extrefsymoff);
	printf("Number of ref symtab entr:\t %u\n", dysym->nextrefsyms);
	printf("Offset to indirect symtab:\t %u\n", dysym->indirectsymoff);
	printf("Number of indirect symtab:\t %u\n", dysym->nindirectsyms);
	printf("Offest to external reloc:\t  %u\n", dysym->extreloff);
	printf("Number of extrenal entr:\t   %u\n", dysym->nextrel);
	printf("Offesst to local reloc:\t    %u\n", dysym->locreloff);
	printf("Number of local reloc:\t     %u\n", dysym->nlocrel);
	printf("\n\n***********************************\n");
}

void		print_symtab(struct symtab_command *symtab)
{
	printf("********************* Symbol Table struct \n");
	printf("symbol table offset:\t        %u\n", symtab->symoff);
	printf("number of table entries:\t    %u\n", symtab->nsyms);
	printf("string table offset:\t        %u\n", symtab->stroff);
	printf("\n\n***************************************\n");
}


void		read_string_table(struct mach_header_64 *header64)
{
	struct load_command 	*loader;
	uint32_t					i;

	loader = (struct load_command *)&header64[1];
	i = 0;
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SYMTAB)
			print_symtab((struct symtab_command *)loader);
		else if (loader->cmd == LC_DYSYMTAB)
			print_dysymtab((struct dysymtab_command *)loader);
		loader = (struct load_command *)((void*)loader + loader->cmdsize);
		i++;
	}
}
