









void		patcher(unsigned char *content, size_t size)
{
	struct mach_header_64		*header64;
	struct load_command			*loader;
	uint64_t					i;

	header64 = (struct mach_header_64 *)header64;
	loader = (struct load_command *)&header64[1];
	i = 0;
	while (i < header64->ncmds)
	{
		if (loader->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64 *seg = (struct segment_command_64*)loader;
			if (strcmp(seg->segname, "__TEXT") == 0)
			{
				struct section_64 *sect = (struct section_64 *)&seg[1];	
			}		
		}
	}
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

	patcher(content, size);

}
