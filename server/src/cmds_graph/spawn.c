/*
** graph_spawn.c for zappy in /home/acker_t/epitech/PSU_2015_zappy/server/src/cmds_graph
**
** Made by tanguy acker
** Login   <acker_t@epitech.net>
**
** Started on  Thu Jun 16 17:59:16 2016 tanguy acker
** Last update Sun Jun 26 21:28:13 2016 wawrzy-j
*/

#include <stdlib.h>
#include "zappy_server.h"

void		graph_all_player(t_server *server, t_client *client)
{
  t_team	*team_tmp;
  t_players	*player_tmp;
  char		*out;

  team_tmp = server->teams;
  while (team_tmp)
    {
      player_tmp = team_tmp->players;
      while (player_tmp)
	{
	  out = new_msg("pnw %d %d %d %d %d %s\n",
			player_tmp->player->id,
			player_tmp->player->pos.x,
			player_tmp->player->pos.y,
			player_tmp->player->orientation + 1,
			player_tmp->player->elevation,
			team_tmp->name);
	  msg_write(server, client, out, 1);
	  player_tmp = player_tmp->next;
	}
      team_tmp = team_tmp->next;
    }
}

void		graph_new_player(t_server *server, t_player *player)
{
  t_client	*tmp;
  char		*out;

  tmp = server->clients;
  out = new_msg("pnw %d %d %d %d %d %s\n",
		player->id, player->pos.x,
		player->pos.y, player->orientation + 1,
		player->elevation, player->team->name);
  if (!out)
    return;
  while (tmp)
    {
      if (tmp->mode == GRAPHIC)
	{
	  msg_write(server, tmp, out, 0);
	  graph_inventory(server, player);
	}
      tmp = tmp->next;
    }
  free(out);
}
