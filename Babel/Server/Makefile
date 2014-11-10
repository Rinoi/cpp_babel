CC		=	g++

RM		=	rm -f

SRCS		=	main.cpp \
			Network/Server.cpp \
			Network/Core.cpp \
			Network/Channel.cpp \
			Network/Room.cpp \
			Network/Session.cpp \
			Database/dbConnection.cpp \
			Plugins/PluginLoaderUnix.cpp \
			../Common/Network/Packet.cpp \
			../Common/Network/PacketManager.cpp \

CPPFLAGS	=	-std=c++11
CPPFLAGS	+=	-W -Wall -Wextra
CPPFLAGS	+=	-I /usr/local/include
CPPFLAGS	+=	-I /usr/local/include/soci
CPPFLAGS	+=	-I /usr/local/Cellar/mysql/5.6.21/include/mysql
CPPFLAGS	+=	-I /usr/include/mysql/

LDFLAGS		=	-lboost_system -lboost_thread -lsoci_core -lsoci_mysql -ldl -L/usr/local/lib -L/usr/local/lib64

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	server

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all
