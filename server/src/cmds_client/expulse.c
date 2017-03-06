/*
** expulse.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:42:46 2016 Sascha Braun
** Last update Sun Jun 26 14:52:57 2016 tanguy acker
*/

#include "zappy_server.h"

static void	expulse_player(t_server *server, t_player *player,
			       t_vector2d *direction)
{
  t_vector2d	orientation;
  t_vector2d	grid[9];
  t_case	*mcase;
  int		i;

  i = -1;
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  case_leave(player, mcase);
  player->pos.x += direction->x;
  player->pos.y += direction->y;
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  case_enter(player, mcase);
  get_direction(&orientation, player->orientation);
  init_directional_grid(grid, &orientation);
  graph_player_pos(server, player);
  if (!player->client)
    return;
  while (++i < 9)
    if (grid[i].x == (-direction->x) && grid[i].y == (-direction->y))
      return (msg_write(server, player->client,
			new_msg("deplacement: %d\n", i), 1));
}

void		cmd_expulse(t_server *server, t_client *client)
{
  t_vector2d	direction;
  t_players	*players;
  t_players	*tmp;
  t_player	*player;
  t_case	*mcase;
  int		cnt;

  if (!client->player)
    return;
  cnt = 0;
  player = client->player;
  get_direction(&direction, player->orientation);
  mcase = get_worldcase(&server->world, player->pos.x, player->pos.y);
  players = mcase->players;
  while (players)
    {
      tmp = players;
      players = players->next;
      if (tmp->player != client->player && ++cnt)
	expulse_player(server, tmp->player, &direction);
    }
  if (!cnt)
    return (msg_write(server, client, "ko\n", 0));
  msg_write(server, client, "ok\n", 0);
}
