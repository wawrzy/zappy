/*
** log.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Thu Jun 16 12:44:32 2016 Sascha Braun
** Last update Mon Jun 20 15:03:41 2016 wawrzy-j
*/

#include <stdio.h>
#include "zappy_server.h"
#include "color.h"

static int	get_linelen(char *str)
{
  int		i;

  i = -1;
  if (!str)
    return (0);
  while (str[++i] && str[i] != '\n');
  return (i);
}

void		log_msg_client(t_server *server, t_client *client,
			       char *msg)
{
  char		*id;

  if (!msg)
    return;
  id = (client->id) ? client->id : "(NULL)";
  printf("%s[%d] Client %s: \"%s\"%s\n", BLUE, server->gameloop.tick,
	 id, msg, NOT);
}

void		log_msg_server(t_server *server, t_client *client,
			       char *msg)
{
  char		*id;
  int		tick;
  int		len;

  id = (client->id) ? client->id : "(NULL)";
  tick = server->gameloop.tick;
  while (msg && msg[0])
    {
      len = get_linelen(msg);
      if (msg[len] == '\n')
  	{
  	  msg[len] = 0;
  	  ++len;
  	}
      printf("%s[%d] Client %s: \"%s\"%s\n", RED, tick, id, msg, NOT);
      msg = &msg[len];
    }
}

void		log_notify(t_server *server, t_client *client,
			   char *msg)
{
  if (!msg)
    return;
  printf(GREEN);
  if (client && client->id)
    printf("[%d] Client %s: %s", server->gameloop.tick, client->id, msg);
  else
    printf("[INFO] %s", msg);
  printf("%s\n", NOT);
}
