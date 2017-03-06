/*
** orientation.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Thu Jun  2 12:51:55 2016 Sascha Braun
** Last update Sat Jun 25 11:59:49 2016 Sascha Braun
*/

#include <stdlib.h>
#include "zappy_server.h"

void		init_orientations(t_vector2d vectors[DIRECTION_NUM])
{
  set_vector2d(&vectors[NORTH], 0, -1);
  set_vector2d(&vectors[OST], 1, 0);
  set_vector2d(&vectors[SOUTH], 0, 1);
  set_vector2d(&vectors[WEST], -1, 0);
}

void		init_directional_grid(t_vector2d vectors[9],
				      t_vector2d *direction)
{
  set_vector2d(&vectors[0], 0, 0);
  set_vector2d(&vectors[1], 1, 0);
  set_vector2d(&vectors[2], 1, -1);
  set_vector2d(&vectors[3], 0, -1);
  set_vector2d(&vectors[4], -1, -1);
  set_vector2d(&vectors[5], -1, 0);
  set_vector2d(&vectors[6], -1, 1);
  set_vector2d(&vectors[7], 0, 1);
  set_vector2d(&vectors[8], 1, 1);
  rotate_vector2d(&vectors[0], direction);
  rotate_vector2d(&vectors[1], direction);
  rotate_vector2d(&vectors[2], direction);
  rotate_vector2d(&vectors[3], direction);
  rotate_vector2d(&vectors[4], direction);
  rotate_vector2d(&vectors[5], direction);
  rotate_vector2d(&vectors[6], direction);
  rotate_vector2d(&vectors[7], direction);
  rotate_vector2d(&vectors[8], direction);
}

void		get_direction(t_vector2d *direction,
			      enum DIRECTION orientation)
{
  t_vector2d	directions[DIRECTION_NUM];

  init_orientations(directions);
  direction->x = directions[orientation].x;
  direction->y = directions[orientation].y;
}

enum DIRECTION	get_random_orientation()
{
  return ((enum DIRECTION)(rand() % DIRECTION_NUM));
}
