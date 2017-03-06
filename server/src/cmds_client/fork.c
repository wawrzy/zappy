/*
** fork.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:43:35 2016 Sascha Braun
** Last update Thu Jun 16 17:53:52 2016 Sascha Braun
*/

#include "zappy_server.h"

void		cmd_fork(t_server *server, t_client *client)
{
  if (!client->player)
    return (msg_write(server, client, "ko\n", 0));
  server->eggs = eggs_add(server->eggs, server, client->player);
  msg_write(server, client, "ok\n", 0);
}
