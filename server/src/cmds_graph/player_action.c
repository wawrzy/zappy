/*
** player_action.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Sat Jun 25 14:29:12 2016 Sascha Braun
** Last update Sun Jun 26 17:51:32 2016 tanguy acker
*/

#include <stdlib.h>
#include "zappy_server.h"

void		graph_start_incantation(t_server *server, t_client *client,
					t_case *mcase)
{
  char		*out;
  t_client	*tmp;
  t_players	*players;

  tmp = server->clients;
  out = new_msg("pic %d %d %d %d\n", client->player->pos.x,
		client->player->pos.y, client->player->elevation,
		client->player->id);
  players = mcase->players;
  if (!out)
    return;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	while (players)
	  {
	    if (client->player->elevation == players->player->elevation)
	      msg_write(server, tmp, out, 0);
	    players = players->next;
	  }
      tmp = tmp->next;
    }
  free(out);
}

void		graph_end_incantation(t_server *server, t_client *client,
			      t_case *mcase)
{
  t_client	*tmp;
  t_players	*players;

  tmp = server->clients;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	{
	  players = mcase->players;
	  graph_bcontent_int(server, tmp, players->player->pos.x,
			     players->player->pos.y);
	  while (players)
	    {
	      if (client->player->elevation == players->player->elevation)
		{
		  msg_write(server, tmp, new_msg("pie %d %d 1\n",
		       players->player->pos.x, players->player->pos.y), 1);
		  graph_player_lvl(server, players->player, tmp);
		}
	      players = players->next;
	    }
	}
      tmp = tmp->next;
    }
}

void		graph_throw(t_server *server, t_player *player, int ressource)
{
  t_client	*tmp;
  char		*out;

  out = new_msg("pdr %d %d\n", player->id, ressource);
  if (!out)
    return;
  tmp = server->clients;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	{
	  msg_write(server, tmp, out, 0);
	  graph_bcontent_int(server, tmp,
			     player->pos.x, player->pos.y);
	}
      tmp = tmp->next;
    }
  free(out);
}

void		graph_take(t_server *server, t_player *player, int ressource)
{
  t_client	*tmp;
  char		*out;

  out = new_msg("pgt %d %d\n", player->id, ressource);
  if (!out)
    return;
  tmp = server->clients;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	{
	  msg_write(server, tmp, out, 0);
	  graph_bcontent_int(server, tmp,
			     player->pos.x, player->pos.y);
	}
      tmp = tmp->next;
    }
  free(out);
}

void		graph_death(t_server *server, t_player *player)
{
  t_client	*tmp;
  char		*out;

  tmp = server->clients;
  out = new_msg("pdi %d\n", player->id);
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
