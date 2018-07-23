
EXEC = s-proc

SRC = s-proc.c

all:
	gcc -o s-proc s-proc.c

clean:
	rm $(EXEC)


