/*
** cases.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Tue Jun 14 11:31:57 2016 Sascha Braun
** Last update Fri Jun 17 14:44:27 2016 Sascha Braun
*/

#include "zappy_server.h"

void		case_enter(t_player *player, t_case *mcase)
{
  if (!player || !mcase)
    return;
  mcase->players = players_add(mcase->players, player);
}

void		case_leave(t_player *player, t_case *mcase)
{
  if (!player || !mcase)
    return;
  mcase->players = players_del(mcase->players,
			       players_get(mcase->players, player));
}
