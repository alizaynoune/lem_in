# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhossan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 20:05:03 by akhossan          #+#    #+#              #
#    Updated: 2020/02/13 16:53:10 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in

CFLAGS	=	-Wall -Werror -Wextra

SRC		=	algorithm.c\
			error.c\
			free.c\
			links.c\
			main.c\
			move.c\
			paths.c\
			print.c\
			rooms.c\
			solution.c\
			tools.c\
			error2.c\
			algo_helper.c\
			tools2.c\
			free2.c

SRCDIR	=	src/

SRCS	=	$(addprefix $(SRCDIR), $(SRC))

OBJDIR	=	objs/

OBJS	=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

LIBS	=	libprintf/libftprintf.a

HEADERS	=	include/lemin.h

INC		=	-I./include

all: $(NAME)

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@gcc $(CFLAGS) $(INC) -c $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(OBJDIR):
	@mkdir -p $@

$(LIBS):
	@make -C libprintf/

$(NAME): $(OBJDIR) $(LIBS) $(OBJS)
	@gcc $(CFLAGS) $(OBJS) $(LIBS) -o $@
	@@echo "\x1B[96mBinary File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"
		
clean:
	@make clean -C libprintf/ 
	@/bin/rm -rf $(OBJDIR)
	@echo "\x1B[96mObjects path \x1B[90;0m[\x1B[34;1m $(OBJDIR) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

fclean: clean
	@make fclean -C libprintf/
	@/bin/rm -rf $(NAME)
	@echo "\x1B[96mBinary File \x1B[90;0m[\x1B[34;1m $(notdir $(NAME)) \x1B[90;0m] \x1B[31mDeleted.\x1B[3    9;0m"

re: fclean all

.PHONY: re clean fclean all

