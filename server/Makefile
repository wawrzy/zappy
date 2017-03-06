##
## Makefile for Makefile in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy
## 
## Made by Sascha Braun
## Login   <braun_s@epitech.net>
## 
## Started on  Wed Jun  1 09:58:39 2016 Sascha Braun
## Last update Sun Jun 26 23:22:17 2016 wawrzy-j
##

SERVER	= ../zappy_server

CC	= gcc
RM	= rm -f

SRC_SER	= src/main.c \
	  src/server.c \
	  src/connections.c \
	  src/time.c \
	  src/clients.c \
	  src/get_cmdline.c \
	  src/messaging.c \
	  src/signals.c \
	  src/user.c \
	  src/orientation.c \
	  src/player.c \
	  src/players.c \
	  src/teams.c \
	  src/commands.c \
	  src/commands_init.c \
	  src/requests.c \
	  src/modes.c \
	  src/ressources.c \
	  src/inventory.c \
	  src/food.c \
	  src/world.c \
	  src/vector2d.c \
	  src/cases.c \
	  src/objects.c \
	  src/log.c \
	  src/eggs.c \
	  src/elevations.c \
	  src/cmds_client/validations.c \
	  src/cmds_client/broadcast.c \
	  src/cmds_client/expulse.c \
	  src/cmds_client/incantation.c \
	  src/cmds_client/incantation_prerequisites.c \
	  src/cmds_client/movements.c \
	  src/cmds_client/putdown_object.c \
	  src/cmds_client/connect_nbr.c \
	  src/cmds_client/fork.c \
	  src/cmds_client/inventory.c \
	  src/cmds_client/pickup_object.c \
	  src/cmds_client/view.c \
	  src/cmds_graph/map_data.c \
	  src/cmds_graph/player_data.c \
	  src/cmds_graph/player_action.c \
	  src/cmds_graph/egg_action.c \
	  src/cmds_graph/usage.c \
	  src/cmds_graph/error.c \
	  src/cmds_graph/spawn.c \
	  src/cmds_graph/position.c \
	  ../utils/sockets.c

OBJ_SER	= $(SRC_SER:.c=.o)

CFLAGS	+= -W -Wall -Wextra
CFLAGS	+= -I./includes

all:
	make $(SERVER)

$(SERVER): $(OBJ_SER)
	$(CC) -o $(SERVER) $(OBJ_SER)

clean:
	$(RM) $(OBJ_SER)

fclean: clean
	$(RM) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
