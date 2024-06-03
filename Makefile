MAKEFLAGS+=silent⠀⠀
HEADER = ./includes/
LIBFT = -lreadline -ltermcap ./libft/libft.a
SRC = srcs/minishell_main.c \
	  srcs/exec/minishell_execution.c \
	  srcs/exec/minishell_special_redirection.c \
	  srcs/parsing/minishell_parsing.c \
	  srcs/exec/builtins/minishell_builtins.c \
	  srcs/utils/minishell_utils.c	\
	  srcs/utils/envp/minishell_envp.c	\
	  srcs/utils/envp/minishell_envp_convert.c \
	  srcs/utils/minishell_freeing.c \
	  srcs/utils/minishell_prompt.c \
	  srcs/utils/signal/minishell_signal.c \
	  srcs/exec/builtins/ft_export/ft_export.c \
	  srcs/exec/builtins/ft_cd/ft_cd.c \
	  srcs/exec/builtins/ft_env/ft_env.c \
	  srcs/exec/builtins/minishell_builtins_child.c \
	  srcs/exec/builtins/ft_cd/ft_cd_linked_list.c
CC = cc
LIB = #-I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib #-lreadline
CFLAGS = -g3 -I $(HEADER) $(LIB) #-fsanitize=address#
OBJ = $(SRC:.c=.o)
NAME = minishell

all : print_art $(NAME)

$(NAME) : $(OBJ)
	make all -C libft/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	echo "\033[32;1mCompilation done! 😊\033[m"
print_art :
	@echo "\033[33;1m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⡳⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⣿⣿⣌⠻⣦⠀⣠⡶⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⠀⢰⣾⣿⣿⠛⣷⣬⣿⠋⢠⣿⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⢀⡀⠀⢸⣿⣿⣿⣟⣛⠿⢦⣽⣦⡞⠉⠛⠶⠞⠁⠀⠙⢷⡄⠀⠀⢀⣀⣀⣤⣤⣴⢳⡄"
	@echo "⠀⠀⠀⠀⠀⢰⣶⣄⣀⣀⣾⣹⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡟⢷⡀⠀⢀⣴⠛⡇⠀⠙⠛⣻⣽⣟⣫⣿⣶⣦⣭⣿⠆⠀⠀⠀⠀⠀⠀⠸⠉⠉⠉⠉⢩⣽⣦⡌⠁⠈⢻"
	@echo "⠀⠀⢤⣤⣀⣠⣷⣿⣯⣥⠿⣯⡽⣿⡞⣻⡟⠀⠀⠀⠀⢰⣤⣄⣀⣸⣇⣬⡿⠶⢿⣅⣸⠇⠀⠀⠈⢻⠛⣋⣥⣤⣿⣄⣀⠀⠀⠀⠀⠀⠿⠙⠀⠀⠀⠀⠀⠀⣻⣿⡿⠀⠀⣼⣿"
	@echo "⣀⠀⢘⣿⣿⣿⣗⣿⣶⣿⣶⠚⣧⣸⠛⢿⡀⠀⠀⠀⠀⠘⢷⡈⣻⡿⣼⠿⢤⣄⣀⡤⠽⣷⣤⠶⢚⡿⠀⣯⡀⠒⠒⠺⢿⣝⣃⣀⣀⠀⠀⠀⠀⠀⣠⣤⣶⣿⣿⡾⠛⣶⢛⡟⠉"
	@echo "⠻⣿⡿⢻⣽⠟⠋⠁⠀⠈⢿⣹⣇⣸⠦⣿⣷⠶⣿⣦⣤⣤⣾⡟⠉⢸⣅⣰⡏⠉⠹⣄⣀⣼⣄⣰⣟⠳⣶⣼⣿⣦⣤⣤⣾⣻⡯⠭⣭⣿⣻⣶⠤⣾⣿⣿⣿⣯⣾⠁⠀⠙⠿⠁⠀"
	@echo "⢠⣯⡴⠋⠁⠀⠀⠀⠀⠀⠘⣿⢤⡟⠲⣿⣷⣾⠋⠘⣷⣈⣿⠛⢺⠋⠰⣯⠟⢻⠉⠹⣄⠀⡉⢿⡙⢿⣍⣿⣿⣛⣿⣿⣿⣧⡀⢀⡀⠉⠛⠻⢿⣿⣿⡿⣿⣿⣿⣧⣀⣴⣄⠀⠀"
	@echo "⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣤⣹⠒⢾⣖⣼⣧⣴⢏⣹⠷⠤⣾⠒⡾⢛⡗⠚⣏⠉⠙⡏⠉⠙⣧⢀⡟⠑⣿⠿⢻⣫⣿⣿⣷⡿⠓⠶⠤⠤⣤⣽⣉⠛⠿⠿⣾⣿⣿⡿⠿⡆⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣧⣸⡛⠺⣇⡼⣟⡿⠯⣏⣀⣠⠷⠴⢷⢿⣿⢭⣹⡉⠉⢻⠒⡾⠛⣿⠧⢺⡇⠀⣸⣿⣟⣿⣿⠁⠀⣠⣶⣆⠀⠀⠉⠙⠓⠲⠶⣯⣥⣴⣦⡇⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡀⢻⡉⢉⣳⣼⣷⣤⣾⣀⣯⣀⣠⣾⡟⢻⣄⣈⡏⠉⢻⣦⡷⠖⢿⠖⠚⡟⢿⠋⠀⢹⣿⣇⣤⣼⠟⣿⣿⡆⠀⠀⠀⠀⠀⠀⠿⠻⠏⠘⠋⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡉⠙⣯⡿⠁⠀⠀⠉⠛⠻⣶⣾⠋⠀⠀⢿⣌⡿⠲⡼⢿⡦⣤⠾⠒⡶⠋⠛⣷⡀⠈⣯⣥⠾⠋⣼⠿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣿⣉⡷⣤⣤⣴⠒⣾⠀⣿⣥⣶⣶⡆⠀⠻⣧⣀⣳⣤⠽⢧⣀⣠⠷⠤⡶⢛⣷⡀⢁⣠⠴⢦⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣩⠟⢻⣿⡛⣻⡟⢀⣼⠿⣿⣿⠇⠀⠀⠙⢧⣀⠘⣳⡤⣞⠁⠀⣘⣷⠟⠁⠛⠋⠁⠀⠈⠙⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⠛⣧⣤⠤⣿⣽⣏⣙⣿⠀⠀⠋⠀⠀⠀⠀⠀⠀⠉⠛⠷⠶⠾⠿⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠟⠀⠀⣿⠿⠛⠉⠉⠀⠀											     \033[m"
clean : 
	make clean -C libft/
	rm -rf $(OBJ)
	echo "\033[31;1mCleaning has been carried out\033[m"
fclean : clean
	make fclean -C libft/
	rm -rf $(NAME)
	echo "\033[31;1mCleaning++ has been carried out 💔\033[m"
re : fclean all $(NAME)
.PHONY: all clean fclean re
