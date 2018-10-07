# machos-lowlevelKit

A collection of tools to assist with analyzing Mach-o binaries. I started this project mainly to learn
about reversing and patching mach-o format files/

It's made up of a collection of tools still in development

## 1. s-proc:
This is a simple script to help generate shellcode from mach-o binaries.

Once run, the resulting shellcode will be stored in a char name[]="" variable in a newly generated .txt
file.
I still need to add the generation of a "#define SHELLCODE_SIZE" variable. It seems important after a few
tests.
```
Make
./s-proc [file]
ls
Makefile s-proc.c s-proc shell.txt file
```
## 2. mread
This is a lightweight version of ELF's readelf found on Linux

When run, it dumps all the sections of an executable you're working on.
It doesn't yet support 32-bit or object files very well due to the nature of how segments are 
laid out differently between executables and objects/libraries/shared objects

Found in the readmach
```
Make all
./mread [binary]
```
Working on flag support as it currently dumps all the contents from top to bottom.

# Testcases

The testcases directory has a few tests-in-progress. 

## Test_blockForge

The first (almost) complete test is the Test_blockForge test. This one entails running the program 'blocker'
to insert a fake section into the text section and then reconstructing the binary to so that tools like
nm and otool behave normally without errors, indicating a successful block forged.

Unfortunately, it no longer runs and I can't tell why yet as i don't know enough about the mach-o format
 to tell why.

Running mread on 'Testing' will show you the inserted fake block (marked __fake_block__)
```
usage:
make
ls
block_forge_main.c lib block.h mread
./blocker blocker __TEXT
ls
blocker block_forge_main.c lib block.h mread Testing
./mread Testing
```

It's still buggy but shows what mread can show you about a binary.

## Test_Textrewrite

The second test is a work-in-progress to assist in patching the text segment of a mach-o binary
Still trying to figure out why this one doesn't run. 
Any help would be greatly appreciated.

-----------------------------------------------------------------------------------------------------------------


# Help Always Appreciated

This is a somewhat minor project in helping me understand the MAC kernel a little better as I'm building these tools
while reading iOS and OSX Kernel Programming by Douglas Clarke and Ole Henry Halvorsen 



It's mainly a hobby project out of fascination for the differences in the Linux vs the Darwin kernels and wanting to
understand a little bit about how they work while making something to improve my practical skills in low level
programming.

Any help would be appreciated if you're interested in helping with the testcases (and in helping me understand why
they keep being (SIG)killed upon running). 

You can reach me at angonyam@student.42.fr























 
 
 


