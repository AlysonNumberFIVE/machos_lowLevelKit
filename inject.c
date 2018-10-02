#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <mach-o/loader.h>
#include  <sys/stat.h>

void	error_and_exit(char *message)
{
	printf("Error : %s\n", message);
	exit(1);
}

int		is_macho_bin64(struct mach_header *header)
{
	if (header->magic == MH_MAGIC_64)
		return (1);
	else 
		return (0);
}

void	map_file(unsigned char **content, size_t *size, char *filename)
{
	int				fd;
	struct stat		info;

	fd = open(filename, O_RDONLY);
	fstat(fd, &info);
	*size = info.st_size;
	*content = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (*content == MAP_FAILED)
		error_and_exit("mmap");
}

struct segment_command_64 *search_section(struct load_command *loader,
		int load_command_num)
{
	int				i;
	struct segment_command_64	*segcomm;

	i = 0;
	while (i < load_command_num)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			segcomm = (struct segment_command_64 *)loader;
			printf("FOUND LC_SEGMENT_64\n");
			break ;
		}
		else
			loader = (struct load_command *)((void*)loader +
					loader->cmdsize);
		i++;
	}
	return (segcomm);
}



void	infect_binary(struct mach_header *header, size_t size)
{
	unsigned char *file;
	struct mach_header_64 *header64;
	struct load_command	*loader;
	struct segment_command_64	*seg_comm;

	file = (unsigned char *)header;
	header64 = (struct mach_header_64 *)header;
	loader = (struct load_command *)&header64[1];
	seg_comm = search_section(loader, header64->ncmds);


}


void	infect_target(unsigned char *content, size_t size)
{
	struct mach_header 		*header;

	header = (struct mach_header*)content;
	if (is_macho_bin64(header) == 1)
		infect_binary(header, size);
	else
		printf("Error ");

}

int		main(int argc, char **argv)
{
	unsigned char		*content;
	size_t				size;

	if (argc != 2)
	{
		printf("Usage : %s <file to infect>\n", argv[0]);
		exit(1);
	}
	map_file(&content, &size, argv[1]);
	infect_target(content, size);
}
