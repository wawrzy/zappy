/*
** view.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:40:18 2016 Sascha Braun
** Last update Thu Jun 16 16:51:50 2016 Sascha Braun
*/

#include "zappy_server.h"

static void	set_ressnames(char *ressnames[RESSOURCE_NUM])
{
  ressnames[FOOD] = " nourriture";
  ressnames[LINEMATE] = " linemate";
  ressnames[DERAUMERE] = " deraumere";
  ressnames[SIBUR] = " sibur";
  ressnames[MENDIANE] = " mendiane";
  ressnames[PHIRAS] = " phiras";
  ressnames[THYSTAME] = " thystame";
}

static void	list_objects(t_server *server, t_client *client,
			     t_case *mcase)
{
  char		*ressnames[RESSOURCE_NUM];
  t_players	*players;
  int		j;
  int		i;

  if (!mcase)
    return;
  players = mcase->players;
  while (players)
    {
      msg_write(server, client, " joueur", 0);
      players = players->next;
    }
  i = -1;
  set_ressnames(ressnames);
  while (++i < RESSOURCE_NUM)
    {
      j = -1;
      while (++j < mcase->objects.ressources[i])
	msg_write(server, client, ressnames[i], 0);
    }
  msg_write(server, client, ",", 0);
}

void		cmd_view(t_server *server, t_client *client)
{
  t_case	*mcase;
  t_vector2d	directions[DIRECTION_NUM];
  t_vector2d	position;
  int		distance;
  int		y;

  if (!client->player)
    return;
  distance = -1;
  init_orientations(directions);
  msg_write(server, client, "{", 0);
  while (++distance <= client->player->elevation)
    {
      y = distance * (-1) - 1;
      while (++y <= distance)
	{
	  set_vector2d(&position, distance, y);
	  rotate_vector2d(&position, &directions[client->player->orientation]);
	  mcase = get_worldcase(&server->world,
				client->player->pos.x + position.x,
				client->player->pos.y + position.y);
	  list_objects(server, client, mcase);
	}
    }
  msg_write(server, client, "}\n", 0);
}
