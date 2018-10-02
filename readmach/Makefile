

EXEC = 	mread

LIB	=  	lib/lib.a

SRC = 	32_or_64.c \
		cmd_args.c \
		load_command_list.c \
		main.c \
		read_header.c

OBJ = $(SRC:.c=.o)

all:
	make -C lib
	gcc -Wall -Werror -Wextra -c $(SRR)
	gcc -o $(EXEC) $(OBJ) $(LIB)

clean:
	make clean -C lib
	rm -f $(OBJ)

fclean:
	make fclean -C lib
	rm -f $(OBJ)
	rm -f $(EXEC)

re: fclean all

