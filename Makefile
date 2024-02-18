# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 16:19:40 by atudor            #+#    #+#              #
#    Updated: 2024/02/10 17:35:45 by atudor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philos
FLAGS	= -Wall -Wextra -Werror -g #-fsanitaze=thread
RM		= rm -rf

SRCS_DIR = ./srcs
SRCS	= main.c check_args.c inits.c utils.c
OBJS_DIR	= ./srcs/obj
OBJS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))


INC	= -I inc/\
	 -I inc/libft/
LIBFT_DIR = inc/libft/
LIBFT_A = $(LIBFT_DIR)/libft.a

$(info $(SRCS))

all: dir $(NAME)
-include $(DEPS)

dir:
	-mkdir -p $(OBJS_DIR)
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c Makefile
	$(CC) -MMD $(FLAGS) -c $< -o $@
	echo $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all
.PHONY:		dir all clean fclean re
.SILENT:

	














