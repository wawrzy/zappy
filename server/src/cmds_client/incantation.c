/*
** incantation.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:43:00 2016 Sascha Braun
** Last update Sat Jun 25 17:00:19 2016 Sascha Braun
*/

#include <stdlib.h>
#include "zappy_server.h"

int		validate_incantation(t_server *server, t_client *client)
{
  t_elevation	*elevation;
  t_player	*player;
  t_case	*mcase;

  player = client->player;
  if (!player || player->elevation >= 8 || player->elevation <= 0)
    return (0);
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  elevation = &server->elevations[player->elevation - 1];
  if (valid_prerequisites(mcase, player, elevation))
    {
      if (!player->incantating)
	{
	  msg_write(server, client, "elevation en cours\n", 0);
	  graph_start_incantation(server, client, mcase);
	}
      player->incantating = 1;
      return (1);
    }
  graph_end_incantation(server, client, mcase);
  player->incantating = 0;
  return (0);
}

void		incantation_success(t_server *server, t_case *mcase,
				    int level)
{
  t_elevation	*elevation;
  t_players	*players;
  t_player	*player;
  char		*msg;

  msg = new_msg("niveau actuel: %d\n", level + 1);
  if (!msg)
    return;
  players = mcase->players;
  while (players)
    {
      player = players->player;
      if (player->elevation == level)
	{
	  player->elevation += 1;
	  if (player->client)
	    msg_write(server, player->client, msg, 0);
	}
      players = players->next;
    }
  elevation = &server->elevations[level - 1];
  elevation_costs(mcase, elevation);
  free(msg);
}

void		cmd_incantation(t_server *server, t_client *client)
{
  t_player	*player;
  t_case	*mcase;
  int		level;

  player = client->player;
  if (!validate_incantation(server, client))
    return (msg_write(server, client, "ko\n", 0));
  level = player->elevation;
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  incantation_success(server, mcase, level);
  graph_end_incantation(server, client, mcase);
  player->incantating = 0;
}
