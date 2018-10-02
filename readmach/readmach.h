
#ifndef READMACH_H
#define READMACH_H

#include <stdio.h>
#include "lib/lib.h"
#include <mach-o/loader.h>

void	read_header(unsigned char *content);
int		is_32_or_64(struct mach_header *head);

#endif
