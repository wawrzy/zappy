/*
** user.c for myirc in /home/braun_s/rendu/Projects/PSU/PSU_2015_myirc/src
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Tue May 17 12:50:19 2016 Sascha Braun
** Last update Thu Jun 16 13:04:00 2016 Sascha Braun
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy_server.h"

static int	valid_res(char *str)
{
  if (!str[0])
    return (0);
  return (1);
}

static char	*parse_cmd(t_client *client, char *str)
{
  int		i;

  i = 0;
  if (str[i] == ':')
    while (str[++i] && str[i] != ' ');
  while (str[i] == ' ')
    ++i;
  str = &str[i];
  i = -1;
  while (str[++i] && str[i] != ' ');
  if (str[i])
    {
      str[i] = 0;
      ++i;
    }
  while (str[i] == ' ')
    ++i;
  client->cmd_args = &str[i];
  return (str);
}

int		handle_user(t_server *server, t_client *client)
{
  t_command	*command;
  char		*cmd;
  char		*str;

  str = get_cmdline(client->sockfd);
  if (str == NULL)
    return (1);
  if (valid_res(str))
    {
      log_msg_client(server, client, str);
      cmd = parse_cmd(client, str);
      command = find_command(server, client, cmd);
      if (command)
	exec_command(server, client, command);
      else if (client->mode == NONE && set_mode(server, client, cmd));
      else
	msg_write(server, client, "ko\n", 0);
    }
  free(str);
  return (0);
}
