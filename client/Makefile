##
## Makefile for makefile in /home/saum_j/PSU/PSU_2015_zappy/src/client
## 
## Made by joan saum
## Login   <saum_j@epitech.net>
## 
## Started on  Mon Jun 13 10:19:11 2016 joan saum
## Last update Sat Jun 25 20:22:46 2016 wawrzy-j
##

NAME = ../zappy_ai

SRC =   src/main.cpp \
        src/Trantorien.cpp \
        src/Network.cpp \
	src/Conversion.cpp \

OBJS = $(SRC:.cpp=.o)

CXXFLAGS += -W -Wall -Wextra -std=c++11
CXXFLAGS += -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	g++ $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
