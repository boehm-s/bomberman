##
## Makefile for  in /home/boehm_s/DEV_C/Libmy/boehm_s/libmy_01
##
## Made by BOEHM Steven
## Login   <boehm_s@etna-alternance.net>
##
## Started on  Sat Oct  4 18:59:41 2014 BOEHM Steven
## Last update Fri Feb  3 15:29:51 2017 BOEHM Steven
##

CC	=	gcc
NAME	=	bomberman-server

SRC	=	game.c		\
		map.c	\
		player.c	\
		queue.c	\
		messaging.c	\
		socket_utils.c	\
		main.c

OBJ	=	$(SRC:%.c=%.o)

RM	=	rm -Rf

GCFLAGS =	gcc -g03 -W -Wall -Werror

LDFLAGS = 	-lpthread -lm

$(NAME)	:	$(OBJ)
		$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(LDFLAGS)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)
		$(RM) *~
		$(RM) #*#

fclean	:	clean
		$(RM) $(NAME)

%.o	:	%.c
		$(GCFLAGS) -c $< -o $@

re	:	fclean all

run	:
		./bomberman-server

.PHONY	:	all clean fclean re run
