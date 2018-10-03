
#include "readmach.h"

void	command_name(uint32_t cmd)
{
	if (cmd == LC_UUID)
		printf("\t\tLC_UUID\n\t\t\t  -> ( struct uuid_command )\n");
	else if (cmd == LC_SEGMENT || cmd == LC_SEGMENT_64)
		printf("\t\tLC_SEGMENT/64\n\t\t\t -> ( struct segment_command\\64 )\n");
	else if (cmd == LC_SYMTAB)
		printf("\t\tLC_SYMTAB\n\t\t\t -> ( struct symtab_command )\n");
	else if (cmd == LC_DYSYMTAB)
		printf("\t\tLC_DYSYMTAB\n\t\t\t -> ( struct dynsymtab_command )\n");
	else if (cmd == LC_THREAD)
		printf("\t\tLC_THREAD\n\t\t\t -> ( struct thread_command )\n");
	else if (cmd == LC_LOAD_DYLIB)
		printf("\t\tLC_LOAD_DYLIB\n\t\t\t -> ( struct dylib_command )\n");
	else if (cmd == LC_ID_DYLIB)
		printf("\t\tLC_ID_DYLIB\n\t\t\t -> ( struct dylib_command )\n");
	else if (cmd == LC_PREBOUND_DYLIB)
		printf("\t\tLC_PREBOUND_DYLIB\n\t\t\t -> ( struct prebound_dylib_command )\n");
	else if (cmd == LC_LOAD_DYLINKER)
		printf("\t\tLC_LOAD_DYLINKER\n\t\t\t -> ( struct dylinker_command )\n");
	else if (cmd == LC_ROUTINES || cmd == LC_ROUTINES_64)
		printf("\t\tLC_ROUTINES\n\t\t\t -> ( struct routines_command\\64 )\n");
	else if (cmd == LC_TWOLEVEL_HINTS)
		printf("\t\tLC_TWOLEVEL_HINTS\n\t\t\t -> ( struct twolevel_hints_command )\n");
	else if (cmd == LC_SUB_FRAMEWORK)
		printf("\t\tLC_SUB_FRAMEWORK\n\t\t\t -> ( struct sub_framework_command )\n");
	else if (cmd == LC_SUB_UMBRELLA)
		printf("\t\tLC_SUB_UMBRELLA\n\t\t\t -> ( struct sub_umbrella_command )\n");
	else if (cmd == LC_SUB_LIBRARY)
		printf("\t\tLC_SUB_LIBRARY\n\t\t\t -> ( struct sub_library_command )\n");
	else if (cmd == LC_SUB_CLIENT)
		printf("\t\tLC_SUB_CLIENT\n\t\t\t -> ( struct sub_client_command )\n");
	else if (cmd == LC_REQ_DYLD)
		printf("\t\tLC_REQ_DYLD\n\t\t\t -> ( command not known\n )\n");
}

void	load_command_list(unsigned char *content)
{
	uint32_t				i;
	struct mach_header		*header;
	struct load_command		*loader;
	struct load_command		*inc;

	header = (struct mach_header *)content;
	loader = (struct load_command *)&header[1];
	i = 0;
	while (i < header->ncmds)
	{
		inc = &loader[i];
		printf("in ->cmd value is %d\n", inc->cmd);
		command_name(inc->cmd);
		i++;	
	}
}


