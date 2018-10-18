

#include <stdio.h>

void 		usage(void)
{
	printf("./mread [options] <binary>\n");
	printf("Options :\n");
	printf("\t\t-h print help menu\n");
	printf("\t\t-H print header information\n");
	printf("\t\t-l list all load command names\n");
	printf("\t\t-S list section information\n");
	printf("\t\t-s string table stats\n");
}

int	main(void)
{
	usage();
}