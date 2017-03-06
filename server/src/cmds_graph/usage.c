/*
** usage.c for zappy in /home/acker_t/epitech/PSU_2015_zappy/server/src/cmds_graph
** 
** Made by tanguy acker
** Login   <acker_t@epitech.net>
** 
** Started on  Tue Jun 14 11:38:54 2016 tanguy acker
** Last update Sun Jun 26 17:51:47 2016 tanguy acker
*/

#include <stdlib.h>
#include "zappy_server.h"

void	graph_get_tick(t_server *server, t_client *client)
{
  char	*out;

  out = new_msg("sgt %d\n", server->gameloop.frequence);
  msg_write(server, client, out, 1);
}

void		graph_end(t_server *server, char *team)
{
  char		*out;
  t_client	*tmp;

  if (!(out = new_msg("seg %s\n", team)))
    return;
  tmp = server->clients;
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

void		graph_server_msg(t_server *server, t_client *client)
{
  char		*out;
  t_client	*tmp;

  if (!(out = new_msg("pbc %d %s\n", client->player->id, client->cmd_args)))
    return;
  tmp = server->clients;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	msg_write(server, tmp, out, 0);
      tmp = tmp->next;
    }
  free(out);
}
