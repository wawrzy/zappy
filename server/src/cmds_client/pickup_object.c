/*
** pickup_object.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:41:58 2016 Sascha Braun
** Last update Tue Jun 21 15:18:49 2016 tanguy acker
*/

#include "zappy_server.h"

void			cmd_pickup_object(t_server *server, t_client *client)
{
  enum RESSOURCE	ressource;
  t_player		*player;
  t_case		*mcase;
  int			*ressnb;

  player = client->player;
  ressource = identify_ressource(client->cmd_args);
  if (ressource == UNKNOWN || !player)
    return (msg_write(server, client, "ko\n", 0));
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  ressnb = &mcase->objects.ressources[ressource];
  if (*ressnb <= 0)
    return (msg_write(server, client, "ko\n", 0));
  player->inventory.ressources[ressource] += 1;
  *ressnb = *ressnb - 1;
  msg_write(server, client, "ok\n", 0);
  graph_take(server, player, ressource);
}
