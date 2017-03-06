/*
** players.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 11:01:22 2016 Sascha Braun
** Last update Thu Jun 23 13:18:07 2016 Sascha Braun
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

t_players	*players_add(t_players *list, t_player *player)
{
  t_players	*tmp;

  if (players_get(list, player))
    return (list);
  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return (list);
  tmp->next = list;
  tmp->player = player;
  return (tmp);
}

t_players	*players_get(t_players *list, t_player *player)
{
  while (list && list->player != player)
    list = list->next;
  return (list);
}

int		players_count(t_players *list)
{
  int		i;

  i = 0;
  while (list && ++i)
    list = list->next;
  return (i);
}

t_players	*players_del(t_players *list, t_players *player)
{
  t_players	*save;
  t_players	*tmp;

  tmp = list;
  save = list;
  if (!list || !player)
    return (list);
  if (list == player)
    {
      list = list->next;
      free(tmp);
      return (list);
    }
  while (list && list->next && list->next != player)
    list = list->next;
  if (list->next == player)
    {
      tmp = list->next;
      list->next = tmp->next;
      free(tmp);
    }
  return (save);
}
