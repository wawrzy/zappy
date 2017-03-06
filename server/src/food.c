/*
** ressources.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Fri Jun  3 16:25:56 2016 Sascha Braun
** Last update Fri Jun 24 10:30:44 2016 tanguy acker
*/

#include "zappy_server.h"

static void	handle_player_death(t_server *server, t_player *player)
{
  t_players	*tmp;
  t_case	*mapcase;

  if (player->client)
    {
      msg_write(server, player->client, "mort\n", 0);
      player->client->player = NULL;
      player->client->quit = 1;
    }
  mapcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  tmp = players_get(mapcase->players, player);
  mapcase->players = players_del(mapcase->players, tmp);
  graph_death(server, player);
  player_del(player);
}

static int	check_food_player(t_server *server, t_player *player)
{
  if (server->gameloop.tick < player->tick_food)
    return (0);
  player->tick_food += FOOD_TIME;
  player->inventory.ressources[FOOD] -= 1;
  graph_inventory(server, player);
  if (player->inventory.ressources[FOOD] <= 0)
    return (1);
  return (0);
}

void		check_food(t_server *server)
{
  t_player	*player;
  t_players	*players;
  t_team	*tmp;

  tmp = server->teams;
  while (tmp)
    {
      players = tmp->players;
      while (players)
	{
	  player = players->player;
	  players = players->next;
	  if (check_food_player(server, player))
	    handle_player_death(server, player);
	}
      tmp = tmp->next;
    }
}
