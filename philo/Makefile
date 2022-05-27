# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 13:55:50 by wismith           #+#    #+#              #
#    Updated: 2022/05/26 23:52:57 by wismith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = philo
SRCS = main parser lifedeath

OBJDIR = OBJECTS
OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o , $(SRCS)))
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(OBJDIR)/%.o : srcs/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)
	tput setaf 2; echo "-> Executable Provided <-"; tput setaf 7;

$(NAME) : $(OBJ)
	tput setaf 6; echo "-> Compiling <-"; tput setaf 7;
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

clean :
	tput setaf 1; echo "-> Cleaning <-"; tput setaf 7;
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

printre :
	tput setaf 4; echo "-> Recreating <-"; tput setaf 7;

re : fclean printre all

.PHONY: all clean fclean re printre