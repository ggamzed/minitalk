NAME	= minitalk
BONUS_NAME = minitalk_bonus
SERVER	= server
CLIENT	= client
BONUS_SERVER = server_bonus
BONUS_CLIENT = client_bonus
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): server.c minitalk.h
	$(CC) $(CFLAGS) server.c -o $(SERVER)

$(CLIENT): client.c minitalk.h
	$(CC) $(CFLAGS) client.c -o $(CLIENT)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_SERVER) $(BONUS_CLIENT)

$(BONUS_SERVER): server_bonus.c minitalk_bonus.h
	$(CC) $(CFLAGS) server_bonus.c -o $(BONUS_SERVER)

$(BONUS_CLIENT): client_bonus.c minitalk_bonus.h
	$(CC) $(CFLAGS) client_bonus.c -o $(BONUS_CLIENT)

clean:
	$(RM) $(SERVER) $(CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT)

fclean: clean

re: fclean all

.PHONY: all clean fclean re bonus