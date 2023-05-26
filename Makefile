# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 16:06:21 by ibouaddi          #+#    #+#              #
#    Updated: 2023/04/14 15:28:34 by amentag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

UTILS = utils/env_utils1.c utils/env_utils2.c utils/utils.c utils/memory_management_utils.c utils/rdir_utils.c \
		utils/herdoc.c utils/env_utils.c utils/buildin_utils.c utils/env_utils3.c\
		utils/main_helper.c

EXECUTING = executing/executing.c executing/executing_helper.c executing/cd.c executing/echo.c executing/env.c executing/exit.c executing/export.c executing/pwd.c executing/unset.c 

SRCS =  main.c parsing/ft_check_input.c lib/lib_helpers.c lib/lib_helpers3.c error/error.c lib/ft_split.c rdirictions/rdirictions.c lib/libft.c memory/memory_managment.c\
		utils/helpers.c parsing/ft_expand_var.c parsing/cmd_helpers.c parsing/store_cmds.c\
		herdoc/hdoc.c signal/signal.c parsing/parsing.c lib/lib_helpers2.c herdoc/herdoc_helpers.c utils/helpers2.c parsing/expand_var_helpers.c herdoc/expand_var_hd.c herdoc/expand_var_hd_helpers.c $(EXECUTING) $(UTILS)

CFLAGS = -Wall -Wextra -Werror
OBJS = ${SRCS:.c=.o}


HEDER = minishell.h

CC = cc

RM = rm -rf


RD_FLAG = -lreadline

all : ${NAME}

${NAME} : ${OBJS} ${HEDER}
	$(CC) $(CFLAGS) -L/Users/amentag/.brew/opt/readline/lib $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o : %.c ${HEDER}
	$(CC) $(CFLAGS) -I/Users/amentag/.brew/opt/readline/include -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${NAME_B}

re: fclean all
