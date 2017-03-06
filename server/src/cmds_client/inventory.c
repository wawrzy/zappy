/*
** inventory.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server/cmds
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 13:46:39 2016 Sascha Braun
** Last update Thu Jun 16 10:56:18 2016 Sascha Braun
*/

#include "zappy_server.h"

void		cmd_inventory(t_server *server, t_client *client)
{
  t_inventory	*inv;
  char		*msg;

  if (!client->player)
    return;
  inv = &client->player->inventory;
  msg = new_msg("{nourriture %d, linemate %d, deraumere %d, sibur %d,\
 mendiane %d, phiras %d, thystame %d}\n",
		inv->ressources[FOOD],
		inv->ressources[LINEMATE],
		inv->ressources[DERAUMERE],
		inv->ressources[SIBUR],
		inv->ressources[MENDIANE],
		inv->ressources[PHIRAS],
		inv->ressources[THYSTAME]);
  msg_write(server, client, msg, 1);
}
