##
## Makefile for zappy in /home/peelou/SVN/zappy-poney/client
## 
## Made by gery baudry
## Login   <baudry_g@epitech.net>
## 
## Started on  Wed Jul  3 10:29:09 2013 gery baudry
## Last update Tue Jul 16 23:36:40 2013 florian dewulf
##

NAME=		client

SRC=		main.cpp

OBJ=		$(SRC:.cpp=.o)

$(NAME):	all

all:		$(OBJ)
		g++ -o $(NAME) $(OBJ) -lpthread

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all