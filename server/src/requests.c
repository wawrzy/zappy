/*
** requests.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Fri Jun  3 12:46:40 2016 Sascha Braun
** Last update Fri Jun  3 13:41:17 2016 Sascha Braun
*/

#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

t_request	*requests_push(t_request *list, t_command *cmd, char *args)
{
  t_request	*end;
  t_request	*tmp;
  int		size;

  size = 0;
  end = list;
  while (end && ++size && end->next)
    end = end->next;
  if (size > MAX_REQUESTS)
    return (list);
  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return (list);
  tmp->next = NULL;
  tmp->command = cmd;
  tmp->args = strdup(args);
  if (!list || !end)
    return (tmp);
  end->next = tmp;
  return (list);
}

int		requests_count(t_request *list)
{
  int		i;

  i = 0;
  while (list && ++i)
    list = list->next;
  return (i);
}

t_request	*requests_pop(t_request *list)
{
  t_request	*tmp;

  if (!list)
    return (list);
  tmp = list;
  list = list->next;
  if (tmp->args)
    free(tmp->args);
  free(tmp);
  return (list);
}
