/*
** ressources.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Fri Jun  3 16:25:56 2016 Sascha Braun
** Last update Sun Jun 26 21:57:05 2016 wawrzy-j
*/

#include <stdlib.h>
#include "zappy_server.h"

enum RESSOURCE	random_ressource(int ress[RESSOURCE_NUM])
{
  int		randnb;
  int		total;
  int		i;

  i = -1;
  total = count_ressources(ress);
  randnb = (total == 0) ? 0 : rand() % total;
  while (++i < RESSOURCE_NUM)
    {
      if (randnb < ress[i])
	return ((enum RESSOURCE)i);
      randnb = randnb - ress[i];
    }
  return (UNKNOWN);
}

static int	world_ressources(t_world *world, int ress[RESSOURCE_NUM])
{
  t_case	*mcase;
  int		mapsize;
  int		i;

  i = -1;
  mapsize = world->width * world->height;
  while (++i < mapsize)
    {
      mcase = &world->cases[i];
      ress[FOOD] += mcase->objects.ressources[FOOD];
      ress[LINEMATE] += mcase->objects.ressources[LINEMATE];
      ress[DERAUMERE] += mcase->objects.ressources[DERAUMERE];
      ress[SIBUR] += mcase->objects.ressources[SIBUR];
      ress[MENDIANE] += mcase->objects.ressources[MENDIANE];
      ress[PHIRAS] += mcase->objects.ressources[PHIRAS];
      ress[THYSTAME] += mcase->objects.ressources[THYSTAME];
    }
  return (count_ressources(ress));
}

static void	update_ressources(t_server *server)
{
  t_client	*clients;
  t_world	*world;
  int		size;
  int		i;

  world = &server->world;
  size = world->width * world->height;
  clients = server->clients;
  while (clients)
    {
      i = -1;
      if (clients->mode == GRAPHIC)
	while (++i < size)
	  if (world->cases[i].need_update == 1)
	    graph_bcontent_int(server, clients,
			       i % world->width,
			       i / world->width);
      clients = clients->next;
    }
  i = -1;
  while (++i < size)
    if (world->cases[i].need_update == 1)
      world->cases[i].need_update = 0;
}

static void		spawn_ressources(t_server *server,
					 int ress[RESSOURCE_NUM],
					 int ress_needed)
{
  enum RESSOURCE	type;
  t_case		*mcase;
  int			i;
  int			x;
  int			y;

  i = -1;
  while (++i < ress_needed)
    {
      x = rand() % 1000;
      y = rand() % 1000;
      mcase = get_worldcase(&server->world, x, y);
      if (count_ressources(mcase->objects.ressources) < MAX_PER_FIELD)
	{
	  type = random_ressource(ress);
	  mcase->objects.ressources[type] += 1;
	  mcase->need_update = 1;
	  ress[type] -= 1;
	}
    }
  if (ress_needed > 0)
    update_ressources(server);
}

void		check_ressources(t_server *server, int randomize)
{
  int		ress[RESSOURCE_NUM];
  int		ress_needed;
  int		ress_max;
  int		ress_cnt;

  if ((server->gameloop.tick % SPAWN_TICKS) != 0)
    return;
  srand(server->gameloop.time_elapsed);
  ress_max = server->world.width * server->world.height;
  if (ress_max < MIN_RESSOURCES)
    ress_max = MIN_RESSOURCES;
  ress_max *= RESS_PER_FIELD;
  init_ressources(ress);
  ress_cnt = world_ressources(&server->world, ress);
  ress_needed = ress_max - ress_cnt;
  ress[FOOD] = USIGNED((FOOD_RATIO * ress_max / 100) - ress[FOOD]);
  ress[LINEMATE] = USIGNED((LINE_RATIO * ress_max / 100) - ress[LINEMATE]);
  ress[DERAUMERE] = USIGNED((DERA_RATIO * ress_max / 100) - ress[DERAUMERE]);
  ress[SIBUR] = USIGNED((SIBU_RATIO * ress_max / 100) - ress[SIBUR]);
  ress[MENDIANE] = USIGNED((MEND_RATIO * ress_max / 100) - ress[MENDIANE]);
  ress[PHIRAS] = USIGNED((PHIR_RATIO * ress_max / 100) - ress[PHIRAS]);
  ress[THYSTAME] = USIGNED((THYS_RATIO * ress_max / 100) - ress[THYSTAME]);
  if (ress_needed > 0)
    spawn_ressources(server, ress,
		     (randomize) ? (rand() % ress_needed) : (ress_needed));
}
