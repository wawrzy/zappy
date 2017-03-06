/*
** position.c for zappy in /home/acker_t/epitech/PSU_2015_zappy/server/src/cmds_graph
** 
** Made by tanguy acker
** Login   <acker_t@epitech.net>
** 
** Started on  Tue Jun 21 11:41:21 2016 tanguy acker
** Last update Tue Jun 21 13:45:26 2016 tanguy acker
*/

#include <stdlib.h>
#include "zappy_server.h"

void		graph_player_pos(t_server *server, t_player *player)
{
  t_client	*tmp;
  char		*out;

  tmp = server->clients;
  out = new_msg("ppo %d %d %d %d\n",
		player->id, player->pos.x,
		player->pos.y, player->orientation + 1);
  if (!out)
    return;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	{
	  msg_write(server, tmp, out, 0);
	}
      tmp = tmp->next;
    }
  free(out);
}
