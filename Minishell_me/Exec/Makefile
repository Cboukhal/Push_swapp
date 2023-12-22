NAME		=	Execution

HEADER		=	../include/

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -g -I $(HEADER)

SRCS		=	boucle_principale.c			\
				Execution.c		\
				Execution2.c	\
				Execution3.c	\
				parsing.c		\
				minishell.c		\

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)	$(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			: fclean all