/*
** objects.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun 16 10:10:13 2016 Sascha Braun
** Last update Fri Jun 17 15:35:16 2016 Sascha Braun
*/

#include <string.h>
#include "zappy_server.h"

enum RESSOURCE	identify_ressource(char *ressource)
{
  char		*ressources[RESSOURCE_NUM];
  int		i;

  i = -1;
  ressources[FOOD] = "nourriture";
  ressources[LINEMATE] = "linemate";
  ressources[DERAUMERE] = "deraumere";
  ressources[SIBUR] = "sibur";
  ressources[MENDIANE] = "mendiane";
  ressources[PHIRAS] = "phiras";
  ressources[THYSTAME] = "thystame";
  while (++i < RESSOURCE_NUM)
    if (strcasecmp(ressources[i], ressource) == 0)
      return ((enum RESSOURCE)i);
  return (UNKNOWN);
}
