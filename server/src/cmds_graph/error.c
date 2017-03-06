/*
** error.c for zappy in /home/acker_t/epitech/PSU_2015_zappy/server/src/cmds_graph
** 
** Made by tanguy acker
** Login   <acker_t@epitech.net>
** 
** Started on  Tue Jun 14 11:41:47 2016 tanguy acker
** Last update Sun Jun 26 17:51:17 2016 tanguy acker
*/

#include "zappy_server.h"

void	graph_unknown_cmd(t_server *server, t_client *client)
{
  msg_write(server, client, "suc\n", 0);
}

void	graph_bad_parameter(t_server *server, t_client *client)
{
  msg_write(server, client, "sbp\n", 0);
}
