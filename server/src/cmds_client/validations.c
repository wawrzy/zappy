/*
** validate_none.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src/cmds_client
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun 16 15:47:02 2016 Sascha Braun
** Last update Thu Jun 16 16:18:45 2016 Sascha Braun
*/

#include "zappy_server.h"

int		validate_args(__attribute__((unused))t_server *server,
			      t_client *client)
{
  if (client->cmd_args[0] == 0)
    return (0);
  return (1);
}

int		validate_none(__attribute__((unused))t_server *server,
			      __attribute__((unused))t_client *client)
{
  return (1);
}
