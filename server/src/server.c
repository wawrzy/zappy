/*
** server.c for myirc in /home/braun_s/rendu/Projects/PSU/myirc_tp/src
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Tue May 17 11:13:20 2016 Sascha Braun
** Last update Sun Jun 26 01:50:32 2016 wawrzy-j
*/

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "zappy_server.h"
#include "sockets.h"

static int	handle_clients(t_server *server, fd_set *readtmp,
			       fd_set *writetmp)
{
  t_client	*client;

  client = server->clients;
  while (client)
    {
      if (!client->quit)
	exec_action(server, client);
      if (!client->quit && FD_ISSET(client->sockfd, readtmp))
	client->quit = handle_user(server, client);
      if (FD_ISSET(client->sockfd, writetmp))
      	handle_write(server, client);
      client = (client->quit && !client->writebuf_pos) ?
      	(handle_deconnection(server, client)) : (client->next);
    }
  return (0);
}

static int		gameloop(t_server *server)
{
  struct timeval	timeout;
  fd_set		writetmp;
  fd_set		readtmp;

  readtmp = server->readfds;
  writetmp = server->writefds;
  timeout.tv_usec = server->gameloop.ticktime;
  timeout.tv_sec = 0;
  if (select(server->fdmax + 1, &readtmp, &writetmp, NULL, &timeout) == -1)
    return (1);
  if (update_gametick(server) == -1)
    return (1);
  check_eggs(server);
  check_food(server);
  check_ressources(server, 1);
  if (FD_ISSET(server->sockfd, &readtmp))
    handle_connection(server);
  handle_clients(server, &readtmp, &writetmp);
  return (0);
}

void		close_server(t_server *server, int exitcode)
{
  t_client	*client;
  t_team	*team;
  t_egg		*eggs;

  client = server->clients;
  while (client)
    {
      shutdown(client->sockfd, SHUT_RDWR);
      close(client->sockfd);
      client = clients_del(client, client);
    }
  team = server->teams;
  while (team)
    team = team_del(team, team);
  eggs = server->eggs;
  while (eggs)
    eggs = eggs_del(eggs, eggs);
  world_free(&server->world);
  log_notify(server, NULL, "Shutdown server");
  close(server->sockfd);
  exit(exitcode);
}

int		start_server(t_server *server)
{
  int		param;

  param = 1;
  server->sockfd = create_socket("TCP");
  FD_ZERO(&server->readfds);
  FD_ZERO(&server->writefds);
  FD_SET(server->sockfd, &server->readfds);
  server->fdmax = server->sockfd;
  if (server->sockfd == -1)
    return (1);
  if (setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, &param, 4) == -1)
    return (1);
  if (bind_socket(server->sockfd, server->port))
    {
      handle_signals(server);
      log_notify(server, NULL, "Startup server");
      server->gameloop.tick = 0;
      server->gameloop.time_elapsed = 0;
      server->gameloop.ticktime = TIME_USEC / server->gameloop.frequence;
      check_ressources(server, 0);
      if (clock_gettime(CLOCK_REALTIME, &server->gameloop.time_start) == 0)
	while (gameloop(server) == 0);
    }
  close_server(server, 1);
  return (0);
}
