/*
** sockets.c for sockets in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Wed Jun  1 17:19:29 2016 Sascha Braun
** Last update Wed Jun  1 18:15:47 2016 Sascha Braun
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include "sockets.h"

int			create_socket(char *protoname)
{
  struct protoent	*pe;
  int			fd;

  pe = getprotobyname(protoname);
  if (!pe)
    return (-1);
  fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (fd == -1)
    perror("socket");
  return (fd);
}

int			bind_socket(int fd, int port)
{
  struct sockaddr_in	s_in_server;
  socklen_t		size;

  size = sizeof(s_in_server);
  s_in_server.sin_family = AF_INET;
  s_in_server.sin_addr.s_addr = INADDR_ANY;
  s_in_server.sin_port = (port == 0) ? 0 : htons(port);
  if (bind(fd, (struct sockaddr *)&s_in_server, size) == -1)
    {
      perror("bind");
      return (-1);
    }
  if (listen(fd, MAX_CONNECTIONS) == -1)
    {
      perror("listen");
      return (-1);
    }
  getsockname(fd, (struct sockaddr *)&s_in_server, &size);
  return (ntohs(s_in_server.sin_port));
}

int			accept_socket(int sockfd, int *fd, char **ip)
{
  struct sockaddr_in	s_in_client;
  socklen_t		s_in_size;

  s_in_size = sizeof(s_in_client);
  if (ip)
    *ip = NULL;
  *fd = accept(sockfd, (struct sockaddr *)&s_in_client, &s_in_size);
  if (*fd == -1)
    {
      perror("accept");
      return (-1);
    }
  if (ip)
    *ip = inet_ntoa(s_in_client.sin_addr);
  return (0);
}
