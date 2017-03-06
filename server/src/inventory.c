/*
** inventory.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Fri Jun 17 13:33:52 2016 Sascha Braun
** Last update Mon Jun 20 15:05:17 2016 wawrzy-j
*/

#include "zappy_server.h"

void		inventory_init(t_inventory *inventory)
{
  init_ressources(inventory->ressources);
}

void		init_ressources(int ress[RESSOURCE_NUM])
{
  ress[FOOD] = 0;
  ress[LINEMATE] = 0;
  ress[DERAUMERE] = 0;
  ress[SIBUR] = 0;
  ress[MENDIANE] = 0;
  ress[PHIRAS] = 0;
  ress[THYSTAME] = 0;
}

int		count_ressources(int ress[RESSOURCE_NUM])
{
  return (ress[FOOD] + ress[LINEMATE] + ress[DERAUMERE] + ress[SIBUR]
	  + ress[MENDIANE] + ress[PHIRAS] + ress[THYSTAME]);
}
