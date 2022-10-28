# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 14:24:38 by mcherrie          #+#    #+#              #
#    Updated: 2022/09/06 20:56:21 by fnochiza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

OBJS	=	$(SRC:%.c=%.o)

HDR	=	minishell.h

NAME	=	minishell

FLAGS = -Werror -Wall -Wextra

SRC			=	z_mini_cd.c \
				z_mini_pwd.c \
				z_mini_env.c \
				z_mini_init.c \
				z_mini_free.c \
				z_mini_exit.c \
				z_mini_main.c \
				z_mini_echo.c \
				z_mini_check.c \
				z_mini_pipex.c \
				z_mini_unset.c \
				z_mini_count.c \
				z_mini_signal.c \
				z_mini_export.c \
				z_mini_struct.c \
				z_mini_utils1.c \
				z_mini_utils2.c \
				z_mini_utils3.c \
				z_mini_utils4.c \
				z_mini_execute.c \
				z_mini_heredoc.c \
				z_mini_ft_atoi.c \
				z_mini_cmd_args.c \
				z_mini_ft_split.c \
				z_mini_redirect.c \
				z_mini_lst_utils.c \
				z_mini_exec_utils.c \
				z_mini_pipe_utils.c \
				z_mini_parse_utils.c \
				z_mini_split_words.c \
				z_mini_struct_utils.c \
				z_mini_builtin_utils.c \
				z_mini_special_simbols.c

RDLN		=	-lreadline -L ~/.brew/Cellar/readline/8.1.2/lib \
				-I~/.brew/Cellar/readline/8.1.2/include

all		:  $(NAME)

%.o	:	%.c  $(HDR) Makefile
	cc $(FLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@ -I $(HDR)

${NAME}: $(OBJS) $(HDR) Makefile
	${CC} ${FLAGS} -g ${OBJS} $(RDLN) -o ${NAME}

clean	:
	rm -rf *.o

fclean	:	clean
	rm -rf $(NAME) ${OBJS}

e	:	fclean all
		rm -rf *.o

re	:	fclean all

.PHONY	: all clean fclean re libft