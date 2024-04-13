Part1 = ft_bzero.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_atoi.c ft_tolower.c ft_toupper.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_calloc.c ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c

Bonus = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

CC = gcc -Wall -Werror -Wextra -I include/
OBJ = $(Part1:.c=.o) $(Part2:.c=.o)
OBJ_BONUS = $(Part1:.c=.o) $(Part2:.c=.o) $(Bonus:.c=.o)
NAME = libft.a

all : $(NAME)

.c.o : 
	$(CC) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJ)
	ar rcs $@ $(OBJ)

bonus: $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ_BONUS)

clean :
	rm -rf $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME)

re : fclean all $(NAME)
