//
// Created by saum_j on 6/13/16.
//

#ifndef RESEAU_HPP
#define RESEAU_HPP

#include <cstring>
#include <iostream>
#include <cstdio>
#include <queue>

class Trantorien;

class Network {

public:
    Network(std::string team_name, int port, std::string computer_name);
    ~Network();

public:
    std::string team_name;
    std::string computer_name;
    int port;
    int fd;

  int check_return(Trantorien *trantorien);
  int listen_server(Trantorien *trantorien);
  void write_to_server(std::queue<std::string> to_send);
};


#endif //RESEAU_HPP
