##
## Makefile for make in /home/mayol_l/rendu/cpp_nibbler
##
## Made by mayol
## Login   <mayol_l@epitech.net>
##
## Started on  Mon Mar 31 18:53:15 2014 mayol
## Last update Mon Nov 10 16:48:26 2014 Michel Benedetti
##

CXX		=	g++

NAME		=	pluginContact.so

CXXFLAGS	=	-Wextra -Wall -W -fPIC -std=c++11 $(INCS)

INCS		=	-I../ -I../../../Common -I../../Database/ -I../../Database/Models/ -I/usr/local/include/soci -I/usr/include/mysql
INCS		+=	-I/usr/local/lib64
INCS		+=	-I../../../Server/Network/
INCS		+=	-I../../../Server/
INCS		+=	-I../../../Common/Network/
INCS		+=      -I /usr/local/include
INCS		+=      -I /usr/local/include/soci
INCS		+=      -I /usr/local/Cellar/boost/1.56.0/include
INCS	        +=      -I /usr/local/Cellar/mysql/5.6.21/include/mysql

LDFLAGS		=	-shared
LDFLAGS		+=	-lboost_system -ldl -lsoci_core -lsoci_mysql -lboost_thread -L/usr/lib64 -lstdc++ -L/usr/local/lib

SRCS		=	src/main.cpp \
			src/Plugin.cpp \
			../../Database/dbConnection.cpp \
			../../../Common/Network/Packet.cpp \

OBJS		=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
