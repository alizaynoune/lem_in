# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 17:08:04 by alzaynou          #+#    #+#              #
#    Updated: 2020/02/13 22:45:22 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra
OBJ_P = objs/
SRC1_P = src/
SRC2_P = libft/
SRC3_P = gnl/
INCLDF = ./includes/ft_printf.h
INCLDL = ./includes/libft.h
INCLDN = ./includes/get_next_line.h
INC_DIR = ./includes

SRC_FILES1 = check.c			\
			 check2.c			\
			 convert.c			\
			 convert2.c			\
			 convert3.c			\
			 convert4.c			\
			 float.c			\
			 float2.c			\
			 ft_precision.c		\
			 ft_precision2.c	\
			 ft_printf.c		\
			 ft_printf2.c		\
			 ft_printf3.c		\
			 printall.c			\
			 printall2.c

SRC_FILES2 = ft_atoi.c			\
			 ft_bzero.c			\
			 ft_isalnum.c		\
			 ft_isalpha.c		\
			 ft_isascii.c		\
			 ft_isdigit.c		\
			 ft_isprint.c		\
			 ft_itoa.c			\
			 ft_lstadd.c		\
			 ft_lstdel.c		\
			 ft_lstdelone.c		\
			 ft_lstiter.c		\
			 ft_lstmap.c		\
			 ft_lstnew.c		\
			 ft_memalloc.c		\
			 ft_memccpy.c		\
			 ft_memchr.c		\
			 ft_memcmp.c		\
			 ft_memcpy.c		\
			 ft_memdel.c		\
			 ft_memmove.c		\
			 ft_memset.c		\
			 ft_putchar.c		\
			 ft_putchar_fd.c	\
			 ft_putendl.c		\
			 ft_putendl_fd.c	\
			 ft_putnbr.c		\
			 ft_putnbr_fd.c		\
			 ft_putstr.c		\
			 ft_putstr_fd.c		\
			 ft_strcat.c		\
			 ft_strchr.c		\
			 ft_strclr.c		\
			 ft_strcmp.c		\
			 ft_strcpy.c		\
			 ft_strdel.c		\
			 ft_strdup.c		\
			 ft_strequ.c		\
			 ft_striter.c		\
			 ft_striteri.c		\
			 ft_strjoin.c		\
			 ft_strlcat.c		\
			 ft_strlen.c		\
			 ft_strmap.c		\
			 ft_strmapi.c		\
			 ft_strncat.c		\
			 ft_strncmp.c		\
			 ft_strncpy.c		\
			 ft_strnequ.c		\
			 ft_strnew.c		\
			 ft_strnstr.c		\
			 ft_strrchr.c		\
			 ft_strsplit.c		\
			 ft_strstr.c		\
			 ft_strsub.c		\
			 ft_strtrim.c		\
			 ft_tolower.c		\
			 ft_toupper.c		\
			 ft_strndup.c		\
			 ft_atoi_all.c		\
			 count_words.c		\
			 remove_last_sapce.c\
			 ft_all_digit.c		\
			 ft_count_char.c

SRC_FILES3 = get_next_line.c

OBJ = $(addprefix $(OBJ_P), $(SRC_FILES1:.c=.o))
OBJ := $(OBJ) $(addprefix $(OBJ_P), $(SRC_FILES2:.c=.o))
OBJ := $(OBJ) $(addprefix $(OBJ_P), $(SRC_FILES3:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\x1B[96mLibrary File \x1B[90;0m[\x1B[34;1m $(notdir $(NAME)) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(OBJ_P)%.o: $(SRC1_P)%.c $(INCLDF)
	@mkdir -p $(OBJ_P)
	@gcc -c $(FLAGS) $< -o $@ -I $(INC_DIR)
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(OBJ_P)%.o: $(SRC2_P)%.c $(INCLDL)
	@mkdir -p $(OBJ_P)
	@gcc -c $(FLAGS) $< -o $@ -I $(INC_DIR)
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(OBJ_P)%.o: $(SRC3_P)%.c $(INCLDN)
	@mkdir -p $(OBJ_P)
	@gcc -c $(FLAGS) $< -o $@ -I $(INC_DIR)
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

clean:
	@rm -rf $(OBJ_P)
	@echo "\x1B[96mObjects path \x1B[90;0m[\x1B[34;1m $(OBJ_P) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\x1B[96mLibrary File \x1B[90;0m[\x1B[34;1m $(notdir $(NAME)) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

re: fclean all

.PHONY: re clean fclean all
