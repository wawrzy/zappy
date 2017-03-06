/*
** commands.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:56:12 2016 Sascha Braun
** Last update Fri Jun 17 15:33:11 2016 Sascha Braun
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

t_command	*find_command(t_server *server, t_client *client, char *cmd)
{
  int		i;

  i = -1;
  if (client->mode == CLIENT)
    while (++i < CMDS_CLI_NUM)
      if (strcasecmp(server->commands_client[i].cmd, cmd) == 0)
	return (&server->commands_client[i]);
  if (client->mode == GRAPHIC)
    while (++i < CMDS_GRA_NUM)
      if (strcasecmp(server->commands_graphic[i].cmd, cmd) == 0)
	return (&server->commands_graphic[i]);
  return (NULL);
}

int		exec_command(t_server *server, t_client *client,
			     t_command *cmd)
{
  t_request	*requests;

  if (!client || !cmd)
    return (0);
  requests = client->requests;
  if (cmd->validate(server, client))
    requests = requests_push(client->requests, cmd, client->cmd_args);
  else
    msg_write(server, client, "ko\n", 0);
  if (!client->requests && requests)
    client->tick_request = server->gameloop.tick + cmd->tickdelay;
  client->requests = requests;
  exec_action(server, client);
  return (1);
}

int		exec_action(t_server *server, t_client *client)
{
  if (!client || !client->requests)
    return (0);
  if (server->gameloop.tick < client->tick_request)
    return (0);
  client->cmd_args = client->requests->args;
  client->requests->command->callback(server, client);
  client->requests = requests_pop(client->requests);
  if (client->requests)
    client->tick_request += client->requests->command->tickdelay;
  return (1);
}
