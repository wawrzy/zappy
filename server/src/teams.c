/*
** teams.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 10:50:56 2016 Sascha Braun
** Last update Thu Jun 23 13:18:31 2016 Sascha Braun
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

t_team		*team_add(t_team *list, char *team)
{
  t_team	*tmp;

  if (team_get(list, team))
    return (list);
  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return (list);
  tmp->next = list;
  tmp->name = strdup(team);
  tmp->players = NULL;
  return (tmp);
}

t_team		*team_get(t_team *list, char *team)
{
  while (list && strcmp(team, list->name) != 0)
    list = list->next;
  return (list);
}

int		team_count_slots(t_server *server, t_team *team)
{
  t_players	*tmp;
  int		unpossessed;
  int		i;

  i = 0;
  unpossessed = 0;
  tmp = team->players;
  while (tmp && ++i)
    {
      if (!tmp->player->client)
	++unpossessed;
      tmp = tmp->next;
    }
  i = server->teamsize - i;
  return (unpossessed + ((i < 0) ? 0 : i));
}

static void	team_free(t_team *tmp)
{
  if (!tmp)
    return;
  if (tmp->name)
    free(tmp->name);
  while (tmp->players)
    tmp->players = players_del(tmp->players, tmp->players);
  free(tmp);
}

t_team		*team_del(t_team *list, t_team *team)
{
  t_team	*save;
  t_team	*tmp;

  tmp = list;
  save = list;
  if (!list || !team)
    return (list);
  if (list == team)
    {
      list = list->next;
      team_free(tmp);
      return (list);
    }
  while (list && list->next && list->next != team)
    list = list->next;
  if (list->next == team)
    {
      tmp = list->next;
      list->next = tmp->next;
      team_free(tmp);
    }
  return (save);
}
