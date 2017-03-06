//
// Created by saum_j on 6/13/16.
//

#include <unistd.h>
#include <sstream>
#include <string>
#include <iostream>
#include "Network.hpp"
#include "Trantorien.hpp"
#include "Conversion.hpp"

void Network::write_to_server(std::queue<std::string> to_send)
{
  std::string lf = "\n";

  while (!to_send.empty()) {
    dprintf(this->fd, "%s", to_send.front().c_str());
    to_send.pop();
  }
  dprintf(this->fd, "%s", lf.c_str());
}

int Network::listen_server(Trantorien *trantorien)
{
  Conversion conv (trantorien->_team);
  char buff[2049];
  int len;
  int retour;
  std::string mot;

  retour = 0;
  if ((len = read(this->fd, buff, 2048)) <= 0)
    exit (1);
  buff[len] = 0;
  std::string mot2;
  std::istringstream iss2(buff);
  std::getline(iss2, mot2, ' ');
  size_t begin;
  std::string direct;
  Conversion convert(trantorien->_team);
  if (mot2 == "message")
  {
    std::string buff2 = buff;
    begin = buff2.find(",");
    direct = std::to_string(atoi(&(buff2[8])));
    buff2 = &buff2[begin + 1];
  }

  std::istringstream iss(buff);
  while (std::getline(iss, mot, '\n')) {
    if (mot == "BIENVENUE") {
      trantorien->connected = true;
    }
    else if (trantorien->getId() == -1) {
      if (mot == "ko")
        exit(1);
      trantorien->setId(atoi(mot.c_str()));
    }
    else if (trantorien->getId() != -1 && trantorien->dim_map == false) {
      trantorien->dim_map = true;
      return (1);
    }
    else if (mot == "mort")
      return (-1);
    trantorien->reponse = mot;
    if ((trantorien->analyse(this)) == 0) {
      retour = 1;
    }
  }
  return (retour);
}

Network::Network(std::string team_name, int port, std::string computer_name) {

    this->team_name = team_name;
    this->port = port;
    this->computer_name = computer_name;
}

Network::~Network() {

}

int		Network::check_return(Trantorien *trantorien)
{
  int           read_mode;

  while (!(read_mode = this->listen_server(trantorien)));
  if (read_mode == -1) {
        return (-1);
      }
  return (0);
}
