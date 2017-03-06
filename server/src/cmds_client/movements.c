/*
** movements.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:39:40 2016 Sascha Braun
** Last update Tue Jun 21 13:05:04 2016 tanguy acker
*/

#include "zappy_server.h"

void		cmd_move_forward(t_server *server, t_client *client)
{
  t_vector2d	direction;
  t_player	*player;
  t_case	*mcase;

  if (!client->player)
    return;
  player = client->player;
  get_direction(&direction, player->orientation);
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  case_leave(player, mcase);
  player->pos.x += direction.x;
  player->pos.y += direction.y;
  player->pos.x = set_worldpos(player->pos.x, server->world.width);
  player->pos.y = set_worldpos(player->pos.y, server->world.height);
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  case_enter(player, mcase);
  msg_write(server, client, "ok\n", 0);
  graph_player_pos(server, player);
}

void		cmd_turn_right(t_server *server, t_client *client)
{
  if (!client->player)
    return;
  client->player->orientation = (enum DIRECTION)
    ((client->player->orientation + 1) % DIRECTION_NUM);
  msg_write(server, client, "ok\n", 0);
  graph_player_pos(server, client->player);
}

void		cmd_turn_left(t_server *server, t_client *client)
{
  int		dir;

  if (!client->player)
    return;
  dir = client->player->orientation - 1;
  if (dir < NORTH)
    dir = WEST;
  client->player->orientation = (enum DIRECTION)dir;
  msg_write(server, client, "ok\n", 0);
  graph_player_pos(server, client->player);
}
