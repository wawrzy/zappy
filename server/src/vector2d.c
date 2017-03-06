/*
** vector2d.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Mon Jun 13 14:29:21 2016 Sascha Braun
** Last update Mon Jun 13 14:57:07 2016 Sascha Braun
*/

#include "zappy_server.h"

void		set_vector2d(t_vector2d *vec, int x, int y)
{
  vec->x = x;
  vec->y = y;
}

void		rotate_vector2d(t_vector2d *vec, t_vector2d *rot)
{
  int		x;

  x = vec->x * rot->x - vec->y * rot->y;
  vec->y = vec->y * rot->x + vec->x * rot->y;
  vec->x = x;
}
