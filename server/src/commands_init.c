/*
** commands_init.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Fri Jun  3 14:11:33 2016 Sascha Braun
** Last update Sun Jun 26 14:57:12 2016 tanguy acker
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

static void	cmd_set(t_command *command, char *cmd, int delay,
			void (*cb)(t_server *, t_client *))
{
  command->cmd = cmd;
  command->tickdelay = delay;
  command->callback = cb;
  command->validate = &validate_none;
}

static void	cmd_validate(t_command *command,
			     int (*validate)(t_server *, t_client *))
{
  command->validate = validate;
}

void		init_commands_client(t_server *server)
{
  cmd_set(&server->commands_client[0], "avance", 7, &cmd_move_forward);
  cmd_set(&server->commands_client[1], "droite", 7, &cmd_turn_right);
  cmd_set(&server->commands_client[2], "gauche", 7, &cmd_turn_left);
  cmd_set(&server->commands_client[3], "voir", 7, &cmd_view);
  cmd_set(&server->commands_client[4], "inventaire", 1, &cmd_inventory);
  cmd_set(&server->commands_client[5], "prend", 7, &cmd_pickup_object);
  cmd_set(&server->commands_client[6], "pose", 7, &cmd_putdown_object);
  cmd_set(&server->commands_client[7], "expulse", 7, &cmd_expulse);
  cmd_set(&server->commands_client[8], "broadcast", 7, &cmd_broadcast);
  cmd_set(&server->commands_client[9], "incantation", 300, &cmd_incantation);
  cmd_set(&server->commands_client[10], "fork", 42, &cmd_fork);
  cmd_set(&server->commands_client[11], "connect_nbr", 0, &cmd_connect_nbr);
  cmd_validate(&server->commands_client[5], &validate_args);
  cmd_validate(&server->commands_client[6], &validate_args);
  cmd_validate(&server->commands_client[8], &validate_args);
  cmd_validate(&server->commands_client[9], &validate_incantation);
}

void		init_commands_graphic(t_server *server)
{
  cmd_set(&server->commands_graphic[0], "msz", 0, &graph_map_size);
  cmd_set(&server->commands_graphic[1], "bct", 0, &graph_bcontent);
  cmd_set(&server->commands_graphic[2], "mct", 0, &graph_mcontent);
  cmd_set(&server->commands_graphic[3], "tna", 0, &graph_team_name);
  cmd_set(&server->commands_graphic[7], "sgt", 0, &graph_get_tick);
}
