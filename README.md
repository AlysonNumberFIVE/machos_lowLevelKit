# machos_s-proc
Executable shellcode generator for MAC-OS similar to s-proc for Linux

Just write assembly code and compile it into an executable (nasm -f macho64 [target.s] -o [target.o]

And run ./s-proc [target.o] to generate shell.txt that will have the executable code from [target.s]
stored in a convenient char [] variable to copy/paste into your project.

