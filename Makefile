# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 16:19:40 by atudor            #+#    #+#              #
#    Updated: 2024/02/25 21:52:35 by atudor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
FLAGS	= -Wall -Wextra -Werror -g -fsanitize=thread
RM		= rm -rf

SRCS_DIR = ./srcs
SRCS	= main.c check_args.c inits.c utils.c
OBJS_DIR	= ./srcs/obj
OBJS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))


INC	= -I inc/


all: dir $(NAME)
-include $(DEPS)

dir:
	-mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c Makefile
	$(CC) -MMD $(FLAGS) -c $< -o $@
	echo $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY:		dir all clean fclean re
.SILENT:

	














