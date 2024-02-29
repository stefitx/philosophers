# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 20:13:56 by atudor            #+#    #+#              #
#    Updated: 2024/02/28 20:13:58 by atudor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= philo_bonus
FLAGS	= -Wall -Wextra -Werror #-g -fsanitize=thread
RM		= rm -rf

HEADER = inc_bonus/philo_bonus.h
SRCS	= srcs_bonus/main_bonus.c srcs_bonus/check_args_bonus.c \
srcs_bonus/inits_bonus.c srcs_bonus/utils_bonus.c srcs_bonus/routine_bonus.c

OBJS = ${SRCS:.c=.o}

%.o:%.c 	$(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: 		${NAME}

${NAME}:	${OBJS}
			gcc ${FLAGS} -o ${NAME} ${OBJS}

clean: 		
			${RM} ${OBJS} ${OBJSBONUS}

fclean: 	clean
			${RM} ${NAME}
			${RM}

re:			fclean all

.PHONY: all clean fclean re
	
