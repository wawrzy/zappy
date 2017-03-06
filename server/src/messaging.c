/*
** broadcast.c for myirc in /home/braun_s/rendu/Projects/PSU/PSU_2015_myirc/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Tue May 17 15:21:19 2016 Sascha Braun
** Last update Sat Jun 25 14:34:59 2016 tanguy acker
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "zappy_server.h"

void		handle_write(t_server *data, t_client *client)
{
  char		*buf;
  int		pos;

  if (!client || !client->writebuf[0])
    return;
  buf = client->writebuf;
  pos = write(client->sockfd, buf, client->writebuf_pos);
  log_msg_server(data, client, buf);
  if (pos < 0)
    return;
  client->writebuf_pos -= pos;
  strcpy(buf, &buf[pos]);
  if (!client->writebuf_pos)
    FD_CLR(client->sockfd, &data->writefds);
}

void		msg_write(t_server *server, t_client *client,
			  char *msg, int bfree)
{
  char		*buf;
  int		msglen;

  if (!msg)
    return;
  buf = client->writebuf;
  msglen = strlen(msg);
  if ((MAX_BUF_SIZE - client->writebuf_pos) < msglen)
    client->writebuf_pos = 0;
  strcpy(&buf[client->writebuf_pos], msg);
  if (bfree)
    free(msg);
  if (!client->writebuf_pos && msglen)
    FD_SET(client->sockfd, &server->writefds);
  client->writebuf_pos += msglen;
}

char		*new_msg(char *fmt, ...)
{
  char		buf[MAX_MSG_SIZE];
  va_list	args;

  buf[0] = 0;
  va_start(args, fmt);
  vsnprintf(buf, MAX_MSG_SIZE, fmt, args);
  va_end(args);
  return (strdup(buf));
}
