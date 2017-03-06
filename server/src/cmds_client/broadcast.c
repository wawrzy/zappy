/*
** broadcast.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Thu Jun  2 13:38:54 2016 Sascha Braun
** Last update Sun Jun 26 01:49:20 2016 wawrzy-j
*/

#include "zappy_server.h"

static void	send_message(t_server *server, t_client *client,
			     t_player *receiver)
{
  t_vector2d	grid[9];
  t_vector2d	direction;
  t_vector2d	diff;
  int		i;

  i = -1;
  set_vector2d(&diff, client->player->pos.x, client->player->pos.y);
  diff.x -= receiver->pos.x;
  diff.y -= receiver->pos.y;
  if (diff.x > (server->world.width / 2))
    diff.x = diff.x - server->world.width;
  else if (diff.x < (-server->world.width / 2))
    diff.x = diff.x + server->world.width;
  if (diff.y > (server->world.height / 2))
    diff.y = diff.y - server->world.height;
  else if (diff.y < (-server->world.height / 2))
    diff.y = diff.y + server->world.height;
  diff.x = (diff.x) ? (diff.x / ABS(diff.x)) : 0;
  diff.y = (diff.y) ? (diff.y / ABS(diff.y)) : 0;
  get_direction(&direction, receiver->orientation);
  init_directional_grid(grid, &direction);
  while (++i < 9)
    if (grid[i].x == diff.x && grid[i].y == diff.y)
      return (msg_write(server, receiver->client,
                        new_msg("message %d,%s\n", i, client->cmd_args), 1));
}

void		cmd_broadcast(t_server *server, t_client *client)
{
  t_players	*players;
  t_team	*team;

  if (!client->player || !client->cmd_args[0])
    return (msg_write(server, client, "ko\n", 0));
  team = server->teams;
  while (team)
    {
      players = team->players;
      while (players)
	{
	  if (players->player != client->player && players->player->client)
	    send_message(server, client, players->player);
	  players = players->next;
	}
      team = team->next;
    }
  msg_write(server, client, "ok\n", 0);
  graph_server_msg(server, client);
}
