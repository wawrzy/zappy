##
## Makefile for make in /home/wawrzy-j/Documents/Projets/PSU/PSU_2015_zappy/graphic
## 
## Made by wawrzy-j
## Login   <wawrzy-j@epitech.net>
## 
## Started on  Mon Jun 13 13:43:52 2016 wawrzy-j
## Last update Sun Jun 26 23:22:46 2016 wawrzy-j
##

GRAPHIC		=	../zappy_graphic

CC		=	g++-4.9

RM		=	rm -f

SRC_GRA		= \
		src/main.cpp \
                src/Network.cpp \
                src/Trantor.cpp \
                src/Case.cpp \
                src/Player.cpp \
                src/Egg.cpp \
		src/AnimationPlayer.cpp \
		src/Frame.cpp \
                src/Protocol.cpp \
		src/MapTrantor.cpp \
                src/Log.cpp \
                src/Content.cpp \
                src/MiniMap.cpp \
                src/Resume.cpp


OBJ_GRA 	=	$(SRC_GRA:.cpp=.o)

CXXFLAGS	+=	-W -Wall -Wextra -std=c++11
CXXFLAGS	+=	-I./includes -I./SFML/include -I./src/

LOADLIB		= -Wl,-rpath=$(shell pwd)/SFML/lib

LIBS        = -L./SFML/lib -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system -lsfml-audio
LIBS        += -ljpeg -lGLEW

$(GRAPHIC): $(OBJ_GRA)
	$(CC) -o $(GRAPHIC) $(OBJ_GRA) $(LIBS) $(LOADLIB)

all: $(GRAPHIC)

.cpp.o:
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ_GRA)

fclean: clean
	$(RM) $(GRAPHIC)

re: fclean all

.PHONY: all clean fclean re
