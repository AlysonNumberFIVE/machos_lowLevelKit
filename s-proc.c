

#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>


int		map_file(char *filename, void **content, size_t *size)
{
	int				fd = open(filename, O_RDONLY);
	struct stat		info;

	fstat(fd, &info);
	*size = info.st_size;
	*content = mmap(0, *size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (*content == MAP_FAILED)
	{
		printf("Error mapping file\n");
		return (-1);
	}
	return (1);
}

void	print_shellcode(uint32_t start, uint64_t length, void *file)
{
	size_t		i;
	size_t		count;
	unsigned char *content;
	FILE	*fd;

	fd = fopen("shell.txt", "w");
	content = (unsigned char *)file;
	i = 0;
	count = start;
	fprintf(fd, "char name[] = \"");
	while (i < length)
	{
		if (content[start] == 0)
			fprintf(fd, "\\x00");
		else if (content[start] < 16)
			fprintf(fd, "\\x0%x", content[start]);
		else
			fprintf(fd, "\\x%x", content[start]);
		start++;
		i++;
	}
	fprintf(fd, "\";");
	fclose(fd);
}

void	shellcode_64(struct mach_header_64 *head, void *file)
{
	struct section_64 *sect;
	uint32_t	start;
	uint64_t	length;
	unsigned char *content;
	char *stuff;

	content = (unsigned char *)file;
	sect = (struct section_64 *)&head[1];
	stuff = (char *)&head[1];
	while (42)
	{
		if (strcmp(stuff, "__text") == 0)
		{
			sect = (struct section_64 *)stuff;
			break ;
		}
		stuff++;
	}
	start = sect->offset;
	length = sect->size;
	print_shellcode(start, length, content);
}

void	s_proc(void *content, size_t size)
{
	struct mach_header *head = (struct mach_header *)content;

	if (head->magic == MH_MAGIC_64)
	{
		struct mach_header_64 *head64 = (struct mach_header_64 *)content;
		shellcode_64(head64, content);
	}
	else 
		printf("error\n");
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage : ./s-proc [shellcode-file]\n");
		return (-1);
	}
	void		*content;
	size_t		size;

	map_file(argv[1], &content, &size);
	s_proc(content, size);
}
