/*
** elevations.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Fri Jun 17 15:58:18 2016 Sascha Braun
** Last update Sat Jun 25 16:30:36 2016 Sascha Braun
*/

#include "zappy_server.h"

void		set_elevation(t_elevation *elevation, int level,
			      int player_num, int costs)
{
  elevation->level = level;
  elevation->player_num = player_num;
  elevation->costs.ressources[FOOD] = 0;
  elevation->costs.ressources[LINEMATE] = (costs / 100000) % 10;
  elevation->costs.ressources[DERAUMERE] = (costs / 10000) % 10;
  elevation->costs.ressources[SIBUR] = (costs / 1000) % 10;
  elevation->costs.ressources[MENDIANE] = (costs / 100) % 10;
  elevation->costs.ressources[PHIRAS] = (costs / 10) % 10;
  elevation->costs.ressources[THYSTAME] = (costs) % 10;
}

void		init_elevations(t_server *server)
{
  set_elevation(&server->elevations[0], 1, 1, 100000);
  set_elevation(&server->elevations[1], 2, 2, 111000);
  set_elevation(&server->elevations[2], 3, 2, 201020);
  set_elevation(&server->elevations[3], 4, 4, 112010);
  set_elevation(&server->elevations[4], 5, 4, 121300);
  set_elevation(&server->elevations[5], 6, 6, 123010);
  set_elevation(&server->elevations[6], 7, 6, 222221);
}

void		elevation_costs(t_case *mcase, t_elevation *elevation)
{
  t_inventory	*costs;
  t_inventory	*inv;

  inv = &mcase->objects;
  costs = &elevation->costs;
  inv->ressources[LINEMATE] -= costs->ressources[LINEMATE];
  inv->ressources[DERAUMERE] -= costs->ressources[DERAUMERE];
  inv->ressources[SIBUR] -= costs->ressources[SIBUR];
  inv->ressources[MENDIANE] -= costs->ressources[MENDIANE];
  inv->ressources[PHIRAS] -= costs->ressources[PHIRAS];
  inv->ressources[THYSTAME] -= costs->ressources[THYSTAME];
}
