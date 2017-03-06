/*
** get_cmdline.c for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Wed Jun  1 18:20:41 2016 Sascha Braun
** Last update Wed Jun  1 18:20:42 2016 Sascha Braun
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

char	*get_cmdline(const int fd)
{
  char	buf[MAX_MSG_SIZE + 1];
  int	readlen;
  int	pos;

  pos = 0;
  buf[0] = 0;
  while (pos < MAX_MSG_SIZE)
    {
      readlen = read(fd, &buf[pos], 1);
      if ((readlen == 0 && pos) || buf[pos] == '\n')
	{
	  buf[pos] = 0;
	  return (strdup(buf));
	}
      if (readlen <= 0)
	return (NULL);
      pos += readlen;
    }
  while ((readlen = read(fd, buf, 1)) > 0 && buf[0] && buf[0] != '\n');
  return (NULL);
}
