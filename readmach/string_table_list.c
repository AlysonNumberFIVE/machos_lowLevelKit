
#include "readmach.h"

void		print_dysymtab(struct dysymtab_command *dysym)
{
	printf("\n\t\t******************* Dynamic Symbol struct \n\n");
	printf("\t\tIndex to local syms:         \t%u\n", dysym->ilocalsym);
	printf("\t\tNumber of local syms:        \t%u\n", dysym->nlocalsym);
	printf("\t\tIndext to external syms:     \t%u\n", dysym->iextdefsym);
	printf("\t\tNumber of external syms:     \t%u\n", dysym->nextdefsym);
	printf("\t\tIndex of undefined syms:     \t%u\n", dysym->iundefsym);
	printf("\t\tNumber of undefine syms:     \t%u\n", dysym->nundefsym);
	printf("\t\tOffset to table of cont:     \t%u\n", dysym->tocoff);
	printf("\t\tNumber of table of cont:     \t%u\n", dysym->ntoc);
	printf("\t\tOffset to module table:      \t%u\n", dysym->modtaboff);
	printf("\t\tNumber of mod table entr:    \t%u\n", dysym->nmodtab);
	printf("\t\tOffset to referenc symtab:   \t%u\n", dysym->extrefsymoff);
	printf("\t\tNumber of ref symtab entr:   \t%u\n", dysym->nextrefsyms);
	printf("\t\tOffset to indirect symtab:   \t%u\n", dysym->indirectsymoff);
	printf("\t\tNumber of indirect symtab:   \t%u\n", dysym->nindirectsyms);
	printf("\t\tOffest to external reloc:    \t%u\n", dysym->extreloff);
	printf("\t\tNumber of extrenal entr:     \t%u\n", dysym->nextrel);
	printf("\t\tOffesst to local reloc:      \t%u\n", dysym->locreloff);
	printf("\t\tNumber of local reloc:       \t%u\n", dysym->nlocrel);
	printf("\n\n\t\t***********************************\n");
}

void		print_symtab(struct symtab_command *symtab)
{
	printf("\n\n\n\n\t\t********************* Symbol Table struct \n\n");
	printf("\t\tsymbol table offset:         \t%u\n", symtab->symoff);
	printf("\t\tnumber of table entries:     \t%u\n", symtab->nsyms);
	printf("\t\tstring table offset:         \t%u\n", symtab->stroff);
	printf("\n\n\t\t***************************************\n");
}


void		read_string_table(struct mach_header_64 *header64)
{
	struct load_command 	*loader;
	uint32_t					i;

	loader = (struct load_command *)&header64[1];
	i = 0;
	printf("\n\n********************** String Information *******\n\n");
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
