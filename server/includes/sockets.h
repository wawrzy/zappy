/*
** sockets.h for sockets in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/src/server
** 
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
** 
** Started on  Wed Jun  1 17:19:43 2016 Sascha Braun
** Last update Wed Jun  1 18:16:36 2016 Sascha Braun
*/

#ifndef SOCKETS_H_
# define SOCKETS_H_

# define MAX_CONNECTIONS	(50)

int		create_socket(char *protoname);
int		bind_socket(int fd, int port);
int		accept_socket(int sockfd, int *fd, char **ip);

#endif /* !SOCKETS_H_ */
