/*
** connect_nbr.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 14:15:05 2016 Sascha Braun
** Last update Thu Jun 16 10:43:37 2016 Sascha Braun
*/

#include "zappy_server.h"

void		cmd_connect_nbr(t_server *server, t_client *client)
{
  char		*msg;

  if (!client->player || !client->player->team)
    return (msg_write(server, client, "0\n", 0));
  msg = new_msg("%d\n", team_count_slots(server, client->player->team));
  msg_write(server, client, msg, 1);
}
