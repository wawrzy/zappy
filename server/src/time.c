/*
** time.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Wed Jun  1 17:02:47 2016 Sascha Braun
** Last update Mon Jun 20 15:04:10 2016 wawrzy-j
*/

#include "zappy_server.h"

static void	diff_timespec(struct timespec *start, struct timespec *end,
			      struct timespec *res)
{
  if ((end->tv_nsec - start->tv_nsec) < 0)
    {
      res->tv_sec = end->tv_sec - start->tv_sec - 1;
      res->tv_nsec = 1000000000 + end->tv_nsec - start->tv_nsec;
    }
  else
    {
      res->tv_sec = end->tv_sec - start->tv_sec;
      res->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
}

static long		get_time_ms(struct timespec *spec)
{
  return ((spec->tv_sec * 1000) + (spec->tv_nsec / 1000000));
}

int			update_gametick(t_server *server)
{
  struct timespec	time_diff;
  long			ms;

  if (clock_gettime(CLOCK_REALTIME, &server->gameloop.time_current) == -1)
    return (1);
  diff_timespec(&server->gameloop.time_start,
		&server->gameloop.time_current,
		&time_diff);
  ms = get_time_ms(&time_diff);
  server->gameloop.time_elapsed = ms;
  server->gameloop.tick = ms / (server->gameloop.ticktime / 1000);
  return (0);
}
