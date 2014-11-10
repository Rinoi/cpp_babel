##
## Makefile for makefile in /home/mayol_l//test/NEW
## 
## Made by lucas mayol
## Login   <mayol_l@epitech.net>
## 
## Started on  Thu Nov  8 16:11:43 2012 lucas mayol
## Last update Sun Jan 13 21:50:38 2013 lucas mayol
##

CXX	=	g++

NAME	=	babel

RM	=	rm -f

CXXFLAGS=	-W -Wall -Wextra -g -I./include

LDFLAG	=	-lportaudio -lopus

SRCS	=	src/main.cpp \
		src/UserPeriph.cpp \
		src/Audio/Input/PortAudio/Periph.cpp \
		src/Audio/Output/PortAudio/Periph.cpp \
		src/Audio/PortAudio/Stream.cpp \
		src/Audio/Opus/Encode.cpp \
		src/Audio/AudioPacket.cpp \

OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAG) $(OBJS) -o $(NAME) $(LDFLAG)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
