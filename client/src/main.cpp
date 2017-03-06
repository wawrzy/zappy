
#include <cstring>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "Trantorien.hpp"
#include "Network.hpp"
#include "Prototype.hpp"

int hostname_to_ip(const char * hostname , char* ip)
{
    struct hostent *host;
    struct in_addr **addr_list;
    int i;

    if ((host = gethostbyname(hostname)) == NULL)
    {
        herror("gethostbyname");
        return 1;
    }
    addr_list = (struct in_addr **) host->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++)
    {
        strcpy(ip , inet_ntoa(*addr_list[i]));
        return 0;
    }

    return 1;
}

Network *parse(char *av[])
{
    std::string team_name;
    std::string computer_name;
    std::string port;

    for(int i = 1; av[i]; i++)
    {
        if (!strcmp(av[i], "-n") && av[i + 1]) {
            team_name = av[i + 1];
        }
        else if (!strcmp(av[i], "-p") && av[i + 1]) {
            port = av[i + 1];
        }
        else if (!strcmp(av[i], "-h") && av[i + 1]) {
            computer_name = av[i + 1];
        }
    }
    if (team_name.empty() || port.empty()) {
        std::cout << "Usage: ./client -n TEAM_NAME -p PORT [-h HOSTNAME]" << std::endl;
        exit(0);
    }
    if (computer_name.empty())
        computer_name = "localhost";
    return new Network(team_name, atoi(port.c_str()), computer_name);
}

void start_game(Network *network)
{
    Trantorien *trantorien = new Trantorien(network->team_name);
    fd_set read_server;
    fd_set write_server;
    int error = 0;

    while (!error)
    {
        FD_ZERO(&read_server);
        FD_ZERO(&write_server);
        FD_SET(network->fd, &read_server);
        FD_SET(network->fd, &write_server);
        if ((select(network->fd + 1, &read_server, &write_server, NULL, NULL)) == -1)
            error = 1;
        else if (FD_ISSET(network->fd, &read_server)) {
            network->listen_server(trantorien);
        }
        else if (FD_ISSET(network->fd, &write_server)) {
	  if (trantorien->launchAI(network) == -1)
	    error = 1;
        }
     }
}

int                     main(__attribute__((unused)) int ac, char *av[])
{
    struct sockaddr_in  s_in;
    struct protoent     *pe;
    int                 fd;
    char                ip[100];

    if (ac == 2)
      return (0);
    Network *network = parse(av);
    if (!(pe = getprotobyname("TCP")))
        return (1);
    if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
        return (1);
    hostname_to_ip(network->computer_name.c_str(), ip);
    network->fd = fd;
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(network->port);
    s_in.sin_addr.s_addr = inet_addr(ip);
    if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
        close(fd);
        return (1);
    }
    start_game(network);
    return (0);
}
