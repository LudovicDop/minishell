MAKEFLAGS+=silent
SRC = minishell_main.c minishell_execution.c minishell_parsing.c
CC = cc
FLAGS = -Wall -Werror -Wextra -g3
OBJ = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	make all -C libft/
	$(CC) $(FLAGS) $(OBJ) -L./libft -lft -o $(NAME) -lreadline -ltermcap
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
