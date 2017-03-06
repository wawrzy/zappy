/*
** players.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 11:01:22 2016 Sascha Braun
** Last update Thu Jun 23 14:35:31 2016 Sascha Braun
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

t_player	*player_new(t_server *server, t_team *team, int x, int y)
{
  static int	player_id = 1;
  t_case	*mcase;
  t_player	*tmp;

  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return (NULL);
  tmp->team = team;
  tmp->client = NULL;
  tmp->orientation = get_random_orientation();
  tmp->tick_food = server->gameloop.tick + FOOD_TIME;
  inventory_init(&tmp->inventory);
  tmp->inventory.ressources[FOOD] = 10;
  tmp->elevation = 1;
  tmp->incantating = 0;
  tmp->pos.x = x;
  tmp->pos.y = y;
  tmp->id = player_id;
  player_team_join(tmp, team);
  mcase = get_worldcase(&server->world, x, y);
  case_enter(tmp, mcase);
  ++player_id;
  return (tmp);
}

t_player	*player_del(t_player *player)
{
  if (!player)
    return (NULL);
  player_team_leave(player);
  free(player);
  return (NULL);
}

int		player_team_join(t_player *player, t_team *team)
{
  t_players	*tmp;

  if (!player || !team)
    return (0);
  tmp = team->players;
  team->players = players_add(team->players, player);
  if (tmp == team->players)
    return (0);
  player->team = team;
  return (1);
}

int		player_team_leave(t_player *player)
{
  t_players	*players;

  if (!player || !player->team)
    return (0);
  players = player->team->players;
  player->team->players = players_del(players, players_get(players, player));
  player->team = NULL;
  return (1);
}
