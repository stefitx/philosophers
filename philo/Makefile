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
FLAGS	= -Wall -Wextra -Werror #-g -fsanitize=thread
RM		= rm -rf

HEADER = inc/philo.h
SRCS	= srcs/main.c srcs/check_args.c srcs/inits.c srcs/utils.c srcs/routine.c

OBJS = ${SRCS:.c=.o}

%.o:%.c 	$(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: 		${NAME}

${NAME}:	${OBJS}
			gcc ${FLAGS} -o ${NAME} ${OBJS}

bonus:		${OBJS} ${OBJSBONUS}
			gcc ${FLAGS} ${NAME} ${OBJS} ${OBJSBONUS}
			@touch $@

clean: 		
			${RM} ${OBJS} ${OBJSBONUS}

fclean: 	clean
			${RM} ${NAME}
			${RM} bonus

re:			fclean all

.PHONY: all clean fclean re
	














