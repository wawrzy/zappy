/*
** player_data.c for zappy in /home/acker_t/epitech/PSU_2015_zappy/server/src/cmds_graph
** 
** Made by tanguy acker
** Login   <acker_t@epitech.net>
**
** Started on  Tue Jun 14 11:30:06 2016 tanguy acker
** Last update Sun Jun 26 17:50:55 2016 tanguy acker
*/

#include <stdlib.h>
#include "zappy_server.h"

void		graph_player_lvl(t_server *server, t_player *player,
			 t_client *client)
{
  char		*out;

  out = new_msg("plv %d %d\n",
		player->id, player->elevation);
  msg_write(server, client, out, 1);
}

void		graph_inventory(t_server *server, t_player *player)
{
  char		*out;
  t_client	*tmp;

  tmp = server->clients;
  out = new_msg("pin %d %d %d %d %d %d %d %d %d %d\n",
		player->id, player->pos.x, player->pos.y,
		player->inventory.ressources[0],
		player->inventory.ressources[1],
		player->inventory.ressources[2],
		player->inventory.ressources[3],
		player->inventory.ressources[4],
		player->inventory.ressources[5],
		player->inventory.ressources[6]);
  if (!out)
    return;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	msg_write(server, tmp, out, 0);
      tmp = tmp->next;
    }
  free(out);
}
