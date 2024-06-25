# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alphan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 13:24:57 by alphan            #+#    #+#              #
#    Updated: 2024/05/03 18:25:26 by alphan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent
SRC = ./ft_is/ft_isalpha.c ./ft_is/ft_isdigit.c ./ft_is/ft_isalnum.c \
./ft_is/ft_isascii.c ./ft_is/ft_isprint.c \
\
./ft_mem/ft_bzero.c ./ft_mem/ft_calloc.c \
./ft_mem/ft_memset.c ./ft_mem/ft_memcpy.c \
./ft_mem/ft_memmove.c ./ft_mem/ft_memchr.c ./ft_mem/ft_memcmp.c \
\
./ft_str/ft_strlcpy.c ./ft_str/ft_strlcat.c ./ft_str/ft_strlen.c \
./ft_str/ft_strchr.c ./ft_str/ft_strrchr.c ./ft_str/ft_strncmp.c \
./ft_str/ft_strnstr.c ./ft_str/ft_strdup.c ./ft_str/ft_substr.c \
./ft_str/ft_strjoin.c ./ft_str/ft_strtrim.c ./ft_str/ft_split.c \
./ft_str/ft_strmapi.c ./ft_str/ft_striteri.c \
\
./ft_to/ft_toupper.c ./ft_to/ft_tolower.c ./ft_to/ft_atoi.c ./ft_to/ft_itoa.c \
./ft_to/ft_atol.c \
\
./ft_put/ft_putchar_fd.c ./ft_put/ft_putstr_fd.c \
./ft_put/ft_putendl_fd.c ./ft_put/ft_putnbr_fd.c \
\
./ft_lst/ft_lstnew.c ./ft_lst/ft_lstadd_front.c \
./ft_lst/ft_lstsize.c ./ft_lst/ft_lstlast.c ./ft_lst/ft_lstadd_back.c \
./ft_lst/ft_lstdelone.c ./ft_lst/ft_lstclear.c ./ft_lst/ft_lstiter.c \
./ft_lst/ft_lstmap.c \
\
./ft_printf/ft_printf.c ./ft_printf/ft_nbr.c \
\
./ft_gnl/get_next_line.c

CC = gcc
CFLAGS = -Werror -Wextra -Wall

OBJ = $(SRC:.c=.o)

NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	@$(AR) -rcs $@ $^

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
