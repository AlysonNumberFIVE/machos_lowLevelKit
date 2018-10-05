
#ifndef READMACH_H
#define READMACH_H

#include <stdio.h>
#include "lib/lib.h"
#include <mach-o/loader.h>


void	read_string_table(struct mach_header_64 *header64);
void	segment_command_list(unsigned char *content);
void	section_list(struct segment_command_64 *segment64);
void	read_header(unsigned char *content);
int		is_32_or_64(struct mach_header *head);
void	load_command_list(unsigned char *content);
char	*cmd_args(int argc, char **argv);

#endif
