NAME		=	minishell

HEADER		=	../include/

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -g -I $(HEADER)

SRCS		=	main.c			\
				other.c			\
				split.c			\
				built.c			\
				echo.c			\
				str.c			\
				strn.c			\
				my.c			\

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)	$(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			: fclean all