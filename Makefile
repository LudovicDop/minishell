#MAKEFLAGS+=silent
HEADER = ./includes/
LIBFT = ./libft/libft.a
SRC = srcs/minishell_main.c \
	  srcs/exec/minishell_execution.c \
	  srcs/exec/minishell_special_carac.c \
	  srcs/parsing/minishell_parsing.c \
	  srcs/exec/builtins/minishell_builtins.c \
	  srcs/utils/minishell_utils.c
CC = gcc
CFLAGS = -g3 -I $(HEADER)
OBJ = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	make all -C libft/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -ltermcap $(LIBFT)
	echo "Done! 😊"
clean : 
	make clean -C libft/
	rm -rf $(OBJ)
	echo "Cleaning has been carried out"
fclean : clean
	make fclean -C libft/
	rm -rf $(NAME)
	echo "Cleaning++ has been carried out"
re : fclean all $(NAME)
.PHONY: all clean fclean re