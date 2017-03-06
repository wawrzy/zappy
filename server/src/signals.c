/*
** signals.c for myirc in /home/braun_s/rendu/Projects/PSU/PSU_2015_myirc/src/server
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Wed May 25 09:26:38 2016 Sascha Braun
** Last update Sat Jun 25 11:16:15 2016 Sascha Braun
*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy_server.h"

static		t_server *g_server;

void		handle_sigint(int sig)
{
  if (sig == SIGINT)
    close_server(g_server, 0);
}

void		handle_signals(t_server *data)
{
  g_server = data;
  signal(SIGINT, &handle_sigint);
}
