/*
** map_data.c for zappy in /home/acker_t/epitech/PSU_2015_zappy/server/src/cmds_graph
** 
** Made by tanguy acker
** Login   <acker_t@epitech.net>
** 
** Started on  Tue Jun 14 11:07:27 2016 tanguy acker
** Last update Fri Jun 24 10:56:54 2016 tanguy acker
*/

#include <stdio.h>
#include <stdlib.h>
#include "zappy_server.h"

void	graph_map_size(t_server *server, t_client *client)
{
  char	*out;

  out = new_msg("msz %d %d\n", server->world.width, server->world.height);
  msg_write(server, client, out, 1);
}

void		graph_bcontent(t_server *server, t_client *client)
{
  t_case	*mcase;
  char		*out;
  int		x;
  int		y;

  x = atoi(client->cmd_args);
  y = -1;
  while (client->cmd_args[++y] != ' ');
  y = atoi(&client->cmd_args[y]);
  if (x >= server->world.width || y >= server->world.height)
    graph_bad_parameter(server, client);
  else
    {
      mcase = get_worldcase(&server->world, x, y);
      out = new_msg("bct %d %d %d %d %d %d %d %d %d\n",
		    x, y, mcase->objects.ressources[FOOD],
		    mcase->objects.ressources[LINEMATE],
		    mcase->objects.ressources[DERAUMERE],
		    mcase->objects.ressources[SIBUR],
		    mcase->objects.ressources[MENDIANE],
		    mcase->objects.ressources[PHIRAS],
		    mcase->objects.ressources[THYSTAME]);
      msg_write(server, client, out, 1);
    }
}

void		graph_bcontent_int(t_server *server, t_client *client,
				   int x, int y)
{
  t_case	*mcase;
  char		*out;

  mcase = get_worldcase(&server->world, x, y);
  out = new_msg("bct %d %d %d %d %d %d %d %d %d\n",
		x, y, mcase->objects.ressources[FOOD],
		mcase->objects.ressources[LINEMATE],
		mcase->objects.ressources[DERAUMERE],
		mcase->objects.ressources[SIBUR],
		mcase->objects.ressources[MENDIANE],
		mcase->objects.ressources[PHIRAS],
		mcase->objects.ressources[THYSTAME]);
  if (!out)
    return;
  msg_write(server, client, out, 0);
  free(out);
}

void		graph_mcontent(t_server *server, t_client *client)
{
  int		x;
  int		y;
  char		*out;
  t_case	*mcase;

  y = -1;
  while (++y != server->world.width)
    {
      x = -1;
      while (++x != server->world.height)
	{
	  mcase = get_worldcase(&server->world, x, y);
	  out = new_msg("bct %d %d %d %d %d %d %d %d %d\n",
			y, x, mcase->objects.ressources[FOOD],
			mcase->objects.ressources[LINEMATE],
			mcase->objects.ressources[DERAUMERE],
			mcase->objects.ressources[SIBUR],
			mcase->objects.ressources[MENDIANE],
			mcase->objects.ressources[PHIRAS],
			mcase->objects.ressources[THYSTAME]);
	  msg_write(server, client, out, 1);
	}
    }
}

void		graph_team_name(t_server *server, t_client *client)
{
  t_team	*tmp;
  char		*out;

  tmp = server->teams;
  while (tmp)
    {
      out = new_msg("tna %s\n", tmp->name);
      msg_write(server, client, out, 1);
      tmp = tmp->next;
    }
}
