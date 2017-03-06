/*
** modes.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Fri Jun  3 15:06:33 2016 Sascha Braun
** Last update Wed Jun 22 12:48:11 2016 tanguy acker
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

static t_player	*get_client_player(t_server *server, t_team *team)
{
  t_players	*players;
  t_player	*player;

  player = NULL;
  srand(server->gameloop.time_elapsed);
  players = team->players;
  while (players && players->player->client)
    players = players->next;
  if (!players)
    player = player_new(server, team, rand() % server->world.width,
			rand() % server->world.height);
  else
    player = players->player;
  return (player);
}

static int	set_mode_client(t_server *server, t_client *client,
				t_team *team)
{
  t_player	*player;
  int		free_slots;

  free_slots = team_count_slots(server, team);
  if (!free_slots)
    return (0);
  player = get_client_player(server, team);
  if (!player)
    return (0);
  --free_slots;
  client->mode = CLIENT;
  client->player = player;
  player->client = client;
  msg_write(server, client, new_msg("%d\n%d %d\n", free_slots,
				    server->world.width,
				    server->world.height), 1);
  graph_new_player(server, player);
  return (1);
}

static int	set_mode_graphic(t_server *server, t_client *client)
{
  client->mode = GRAPHIC;
  graph_map_size(server, client);
  graph_get_tick(server, client);
  graph_mcontent(server, client);
  graph_team_name(server, client);
  graph_all_player(server, client);
  return (1);
}

int		set_mode(t_server *server, t_client *client, char *mode)
{
  t_team	*tmp;

  if (strcasecmp("GRAPHIC", mode) == 0)
    return (set_mode_graphic(server, client));
  tmp = server->teams;
  while (tmp)
    {
      if (strcmp(tmp->name, mode) == 0)
	return (set_mode_client(server, client, tmp));
      tmp = tmp->next;
    }
  return (0);
}
