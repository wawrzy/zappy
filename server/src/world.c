/*
** world.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:31:03 2016 Sascha Braun
** Last update Sat Jun 25 15:12:01 2016 Sascha Braun
*/

#include <stdlib.h>
#include "zappy_server.h"

int		set_worldpos(int val, int max)
{
  val = val % max;
  if (val < 0)
    val += max;
  return (val);
}

t_case		*get_worldcase(t_world *world, int x, int y)
{
  int		idx;

  x = set_worldpos(x, world->width);
  y = set_worldpos(y, world->height);
  idx = world->width * y + x;
  return (&world->cases[idx]);
}

int		world_generate(t_world *world)
{
  int		size;
  int		i;

  world->cases = NULL;
  if (!world->width || !world->height)
    return (0);
  size = world->width * world->height;
  world->cases = malloc(sizeof(*world->cases) * size);
  if (!world->cases)
    return (0);
  i = -1;
  while (++i < size)
    {
      world->cases[i].players = NULL;
      world->cases[i].need_update = 0;
      inventory_init(&world->cases[i].objects);
    }
  return (1);
}

void		world_free(t_world *world)
{
  t_players	*players;
  int		size;
  int		i;

  i = -1;
  size = world->width * world->height;
  if (!world->cases)
    return;
  while (++i < size)
    {
      players = world->cases[i].players;
      while (players)
	players = players_del(players, players);
      world->cases[i].players = NULL;
    }
  if (world->cases)
    free(world->cases);
}
