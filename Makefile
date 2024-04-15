SRC = minishell_main.c
CC = cc
FLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	make all -C libft/
	$(CC) $(FLAGS) $(OBJ) -L./libft -lft -o $(NAME) -lreadline
	echo "Done!"
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
