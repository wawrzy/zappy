/*
** egg_action.c for zappy in /home/acker_t/epitech/PSU_2015_zappy/server/src/cmds_graph
** 
** Made by tanguy acker
** Login   <acker_t@epitech.net>
** 
** Started on  Tue Jun 14 11:34:29 2016 tanguy acker
** Last update Sun Jun 26 17:50:31 2016 tanguy acker
*/

#include <stdlib.h>
#include "zappy_server.h"

void		graph_new_egg(t_server *server, t_egg *egg, t_player *player)
{
  char		*out;
  t_client	*tmp;

  out = new_msg("enw %d %d %d %d\n",
		egg->id, player->id,
		egg->pos.x, egg->pos.y);
  tmp = server->clients;
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

void		graph_birth(t_server *server, t_egg *egg)
{
  char		*out;
  t_client	*tmp;

  out = new_msg("eht %d\n",
		egg->id);
  tmp = server->clients;
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
