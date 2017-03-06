/*
** eggs.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun 16 17:02:49 2016 Sascha Braun
** Last update Sun Jun 26 14:15:10 2016 Sascha Braun
*/

#include <stdlib.h>
#include "zappy_server.h"

t_egg		*eggs_add(t_egg *list, t_server *server, t_player *parent)
{
  static int	id = 1;
  t_egg		*tmp;

  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return (list);
  tmp->next = NULL;
  tmp->pos.x = parent->pos.x;
  tmp->pos.y = parent->pos.y;
  tmp->team = parent->team;
  tmp->tick_eclosion = server->gameloop.tick + ECLOSION_TIME;
  tmp->id = id;
  ++id;
  graph_new_egg(server, tmp, parent);
  return (tmp);
}

static void	egg_free(t_egg *egg)
{
  if (!egg)
    return;
  free(egg);
}

t_egg		*eggs_del(t_egg *list, t_egg *egg)
{
  t_egg		*save;
  t_egg		*tmp;

  tmp = list;
  save = list;
  if (!list || !egg)
    return (list);
  if (list == egg)
    {
      list = list->next;
      egg_free(tmp);
      return (list);
    }
  while (list && list->next && list->next != egg)
    list = list->next;
  if (list->next == egg)
    {
      tmp = list->next;
      list->next = tmp->next;
      egg_free(tmp);
    }
  return (save);
}

static void	handle_egg_eclosion(t_server *server, t_egg *egg)
{
  t_player	*player;

  if (!egg->team)
    return;
  player = player_new(server, egg->team, egg->pos.x, egg->pos.y);
  egg->team->players = players_add(egg->team->players, player);
  graph_birth(server, egg);
  graph_new_player(server, player);
}

void		check_eggs(t_server *server)
{
  t_egg		*eggs;
  t_egg		*tmp;

  eggs = server->eggs;
  while (eggs)
    {
      tmp = eggs;
      eggs = eggs->next;
      if (server->gameloop.tick >= tmp->tick_eclosion)
	{
	  handle_egg_eclosion(server, tmp);
	  server->eggs = eggs_del(server->eggs, tmp);
	}
    }
}
