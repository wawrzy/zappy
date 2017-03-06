/*
** clients.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Wed Jun 15 09:15:49 2016 Sascha Braun
** Last update Thu Jun 23 13:42:30 2016 Sascha Braun
*/

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "zappy_server.h"

t_client	*clients_add(t_client *list, t_server *server,
			     int fd, char *ip)
{
  t_client	*tmp;

  tmp = malloc(sizeof(*tmp));
  if (tmp == NULL)
    return (list);
  tmp->mode = NONE;
  tmp->quit = 0;
  tmp->next = list;
  tmp->sockfd = fd;
  memset(tmp->writebuf, 0, MAX_BUF_SIZE);
  tmp->writebuf_pos = 0;
  tmp->ip = strdup(ip);
  tmp->id = new_msg("C%lx%x", server->gameloop.time_elapsed,
		    rand() % (0xFFFF));
  tmp->player = NULL;
  tmp->requests = NULL;
  return (tmp);
}

static void	client_free(t_client *client)
{
  if (!client)
    return;
  while (client->requests)
    client->requests = requests_pop(client->requests);
  if (client->player)
    client->player->client = NULL;
  if (client->ip)
    free(client->ip);
  if (client->id)
    free(client->id);
  free(client);
}

t_client	*clients_del(t_client *list, t_client *client)
{
  t_client	*tmp;

  tmp = list;
  if (!list || !client)
    return (list);
  if (list == client)
    {
      list = list->next;
      client_free(tmp);
      return (list);
    }
  while (list && list->next && list->next != client)
    list = list->next;
  if (list->next == client)
    {
      tmp = list->next;
      list->next = tmp->next;
      client_free(tmp);
    }
  if (list)
    list = list->next;
  return (list);
}

int		clients_fdmax(t_client *list)
{
  int		max;

  max = 0;
  while (list)
    {
      if (list->sockfd > max)
	max = list->sockfd;
      list = list->next;
    }
  return (max);
}
