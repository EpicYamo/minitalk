NAME			=	minitalk
CLIENT			=	client
CLIENT_B		=	client_bonus
SERVER			=	server
SERVER_B		=	server_bonus
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

all:			$(NAME)
bonus:			${CLIENT_B} ${SERVER_B}

$(NAME): $(SERVER) $(CLIENT)

${CLIENT}:		ft_client.c
				${CC} ${CFLAGS} -o client ft_client.c

${SERVER}:		ft_server.c
				${CC} ${CFLAGS} -o server ft_server.c

${CLIENT_B}:	ft_client_bonus.c
				${CC} ${CFLAGS} -o client_bonus ft_client_bonus.c

${SERVER_B}:	ft_server_bonus.c
				${CC} ${CFLAGS} -o server_bonus ft_server_bonus.c

clean:
				$(RM) $(SERVER) $(CLIENT) ${CLIENT_B} ${SERVER_B}

fclean:			clean

re:				fclean all

.PHONY:			all $(NAME) bonus clean fclean re
