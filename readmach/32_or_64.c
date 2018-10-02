
#include <mach-o/loader.h>

int		is_32_or_64(struct mach_header *head)
{
	if (head->magic == MH_MAGIC)	
		return 32;
	else
		return 64;
}
