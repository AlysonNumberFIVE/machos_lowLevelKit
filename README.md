# machos_s-proc
Executable code generator for MAC-OS similar to s-proc

Similar to s-proc for Linux shellcode generation.

Just write assembly code and compile it into an executable (nasm -f macho64 [target.s] -o [target.o]

And run ./s-proc [target.o] to generate shell.txt that will have the executable code from [target.s]
stored in a convenient char [] variable to copy/paste into your project.

