/*
** main.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Wed Jun  1 16:00:22 2016 Sascha Braun
** Last update Sat Jun 25 14:53:08 2016 Sascha Braun
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy_server.h"

static int	parse_teams(char *flag, t_server *server, char ***args)
{
  char		**av;
  int		i;

  i = 0;
  av = *args;
  if (av[0] == NULL || av[1] == NULL ||
      strcmp(flag, av[0]) != 0 || av[1][0] == '-')
    return (0);
  while (av[++i] && av[i][0] != '-')
    server->teams = team_add(server->teams, av[i]);
  *args = &av[i];
  return (1);
}

static int	parse_int(char *flag, int *val, char ***args)
{
  char		**av;

  av = *args;
  if (av[0] == NULL || av[1] == NULL ||
      strcmp(flag, av[0]) != 0 || av[1][0] == '-')
    return (0);
  *val = atoi(av[1]);
  *args = &av[2];
  return (1);
}

static int	parse_args(t_server *server, char **av, char *err)
{
  ++av;
  while (*av)
    {
      if (!parse_int("-p", &server->port, &av) &&
	  !parse_int("-x", &server->world.width, &av) &&
	  !parse_int("-y", &server->world.height, &av) &&
	  !parse_int("-c", &server->teamsize, &av) &&
	  !parse_int("-t", &server->gameloop.frequence, &av) &&
	  !parse_teams("-n", server, &av))
	{
	  fprintf(stderr, "%s: %s\n", err, *av);
	  return (1);
	}
    }
  return (0);
}

static void	init_server(t_server *server)
{
  server->port = 0;
  server->teamsize = 0;
  server->world.width = 0;
  server->world.height = 0;
  server->gameloop.frequence = 100;
  server->clients = NULL;
  server->teams = NULL;
  server->eggs = NULL;
  init_elevations(server);
  init_commands_client(server);
  init_commands_graphic(server);
}

int		main(int ac __attribute__((unused)), char **av)
{
  t_server	server;

  init_server(&server);
  if (parse_args(&server, av, "Invalid argument") == 1)
    return (1);
  if (server.port <= 0 ||
      server.teamsize <= 0 ||
      server.world.width <= 0 ||
      server.world.height <= 0 ||
      server.teams == NULL)
    {
      fprintf(stderr, "Usage: %s\n\
 -p port\n\
 -x width of the world\n\
 -y height of the world\n\
 -n name_of_team_1 name_of_team_2 ...\n\
 -c number of clients allowed at the game beginning\n\
 -t time delay for executing actions (frequence).\n", av[0]);
      return (1);
    }
  if (world_generate(&server.world) == 0)
    return (1);
  return (start_server(&server));
}
