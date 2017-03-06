/*
** connections.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Sat Jun 25 11:08:11 2016 Sascha Braun
** Last update Sat Jun 25 11:29:41 2016 Sascha Braun
*/

#include <sys/select.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "zappy_server.h"
#include "sockets.h"

void		handle_connection(t_server *data)
{
  t_client	*clients;
  char		*msg;
  char		*ip;
  int		fd;

  if (accept_socket(data->sockfd, &fd, &ip) != -1)
    {
      clients = clients_add(data->clients, data, fd, ip);
      if (clients == data->clients)
        return;
      data->clients = clients;
      FD_SET(fd, &data->readfds);
      if (fd > data->fdmax)
        data->fdmax = fd;
      msg = new_msg("Connected on %s", ip);
      log_notify(data, data->clients, msg);
      if (msg)
        free(msg);
      msg_write(data, data->clients, "BIENVENUE\n", 0);
    }
  else
    close_server(data, 1);
}

t_client	*handle_deconnection(t_server *data, t_client *client)
{
  t_client	*tmp;
  int		fd;

  fd = client->sockfd;
  FD_CLR(fd, &data->readfds);
  FD_CLR(fd, &data->writefds);
  shutdown(fd, SHUT_RDWR);
  close(fd);
  log_notify(data, client, "Deconnected");
  tmp = clients_del(data->clients, client);
  if (data->clients == client)
    data->clients = tmp;
  if (fd == data->fdmax)
    data->fdmax = clients_fdmax(data->clients);
  if (data->fdmax == 0)
    data->fdmax = data->sockfd;
  return (tmp);
}
