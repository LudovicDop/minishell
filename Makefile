#MAKEFLAGS+=silent
HEADER = ./includes/
LIBFT = -lreadline -ltermcap ./libft/libft.a
SRC = srcs/minishell_main.c \
	  srcs/exec/minishell_execution.c \
	  srcs/exec/minishell_special_carac.c \
	  srcs/parsing/minishell_parsing.c \
	  srcs/exec/builtins/minishell_builtins.c \
	  srcs/utils/minishell_utils.c	\
	  srcs/utils/envp/minishell_envp.c	\
	  srcs/utils/envp/minishell_envp_convert.c \
	  srcs/utils/minishell_freeing.c \
	  srcs/utils/minishell_prompt.c \
	  srcs/utils/signal/minishell_signal.c
CC = cc
CFLAGS = -g3 -I $(HEADER) -fsanitize=address
OBJ = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	make all -C libft/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	echo "Done! 😊"
clean : 
	make clean -C libft/
	rm -rf $(OBJ)
	echo "Cleaning has been carried out"
fclean : clean
	make fclean -C libft/
	rm -rf $(NAME)
	echo "Cleaning++ has been carried out 💔"
re : fclean all $(NAME)
.PHONY: all clean fclean re
