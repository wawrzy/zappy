/*
** incantation_prerequisites.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src/cmds_client
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Sat Jun 25 13:47:54 2016 Sascha Braun
** Last update Sat Jun 25 13:47:56 2016 Sascha Braun
*/

#include "zappy_server.h"

int		count_lvlplayers(t_players *players, int level)
{
  int		i;

  i = 0;
  while (players)
    {
      if (players->player->elevation == level)
        ++i;
      players = players->next;
    }
  return (i);
}

int		is_incantating(t_players *players, t_player *player)
{
  while (players)
    {
      if (players->player != player &&
          players->player->client &&
          players->player->incantating)
        return (1);
      players = players->next;
    }
  return (0);
}

int		valid_prerequisites(t_case *mcase, t_player *player,
                                    t_elevation *elevation)
{
  int		players_num;
  int		*ress;

  ress = mcase->objects.ressources;
  players_num = count_lvlplayers(mcase->players, elevation->level);
  if (players_num == elevation->player_num &&
      is_incantating(mcase->players, player) == 0 &&
      ress[LINEMATE] == elevation->costs.ressources[LINEMATE] &&
      ress[DERAUMERE] == elevation->costs.ressources[DERAUMERE] &&
      ress[SIBUR] == elevation->costs.ressources[SIBUR] &&
      ress[MENDIANE] == elevation->costs.ressources[MENDIANE] &&
      ress[PHIRAS] == elevation->costs.ressources[PHIRAS] &&
      ress[THYSTAME] == elevation->costs.ressources[THYSTAME])
    return (1);
  return (0);
}
