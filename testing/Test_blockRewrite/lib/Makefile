

NAME = lib

SRC = strtrim.c arraylen.c arraypush.c charpush.c count_args.c free2d.c free_and_null.c itoa.c join.c my_isspace.c read_buffer.c split.c sub.c normalize_string.c ft_memset.c ft_bzero.c ft_strcat.c ft_strcpy.c ft_strcmp.c ft_strlen.c ft_strdup.c ft_strstr.c ft_strchr.c map_file.c

LIB = lib.a

OBJ = $(SRC:.c=.o)

$(NAME):
	gcc -Wall -Werror -Wextra -c $(SRC)
	ar rc $(LIB) $(OBJ)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(LIB)

re: fclean all
