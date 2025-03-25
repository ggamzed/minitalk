SRCS_CLIENT	=			client.c utils.c
SRCS_SERVER	=			server.c utils.c
SRCS_CLIENT_BONUS =		client_bonus.c utils_bonus.c
SRCS_SERVER_BONUS =		server_bonus.c utils_bonus.c

OBJS_CLIENT	=			$(SRCS_CLIENT:.c=.o)
OBJS_SERVER	=			$(SRCS_SERVER:.c=.o)
OBJS_CLIENT_BONUS =		$(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS =		$(SRCS_SERVER_BONUS:.c=.o)

CC			=			gcc
RM			=			rm -f
CFLAGS		=			-Wall -Wextra -Werror

NAME_CLIENT	=			client
NAME_SERVER	=			server
NAME_BONUS_CLIENT	=	client_bonus
NAME_BONUS_SERVER	=	server_bonus

all:					$(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT):			$(OBJS_CLIENT)
					$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER):			$(OBJS_SERVER)
					$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

bonus:					$(NAME_BONUS_CLIENT) $(NAME_BONUS_SERVER)

$(NAME_BONUS_CLIENT):	$(OBJS_CLIENT_BONUS)
					$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -o $(NAME_BONUS_CLIENT)

$(NAME_BONUS_SERVER):	$(OBJS_SERVER_BONUS)
					$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -o $(NAME_BONUS_SERVER)

clean:
					$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)

fclean:	clean
					$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_BONUS_CLIENT) $(NAME_BONUS_SERVER)

re:		fclean all

.PHONY:	all clean fclean re bonus
