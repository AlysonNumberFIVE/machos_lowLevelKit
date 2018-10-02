
#include "readmach.h"

void	load_command_list(unsigned char *content)
{
	if (is_32_or_64((struct mach_header *)content) == 64)
	{
		printf("value is 64");

	}
}
