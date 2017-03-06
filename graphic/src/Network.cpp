
#include <iostream>
#include <strings.h>
#include "Network.hpp"
#include "Error.hpp"

Network::Network(std::string server, int port)
{
    this->_server = server;
    this->_port = port;
}

Network::~Network()
{
}

void    Network::initSocket()
{
    sf::IpAddress server;

    server = this->_server.c_str();
    if (server == sf::IpAddress::None) {
        throw Error("FAIL CONNECT TO SERVER");
        return;
    }
    
    if (this->_socket.connect(server, this->_port) != sf::Socket::Done)
    {
        throw Error("FAIL CONNECT TO SERVER (connect)");
        return;
    }
    this->_selector.add(this->_socket);
    
    sf::Time time = sf::seconds(10.0f);
    if (this->_selector.wait(time))
    {
        if (this->readServerLine() != "BIENVENUE")
          throw Error("FAIL CONNECT TO SERVER (msg BVN)");
    }
    else
       throw Error("FAIL CONNECT TO SERVER (Timeout msg BVN)");
    
    std::cout << "Connected to server !"<< std::endl;
}

std::string     Network::readServer()
{
     char        in[1024];
     std::string    ret;
     std::size_t received;
     
     received = 1024;
     while (received == 1024) {
        bzero(in, 1024);
        if (this->_socket.receive(in, sizeof(in), received) != sf::Socket::Done)
            return (ret);
        ret.append(in, received);   
     }

    return (ret);
}

std::string     Network::readServerLine()
{
     char        in[1];
     std::string    ret;
     std::size_t received;
     
     received = 1;
     while (received == 1) {
        bzero(in, 1);
        if (this->_socket.receive(in, sizeof(in), received) != sf::Socket::Done)
            return (ret);
        if (received == 0)
            return (ret);
        if (in[0] == '\n')
            break;
        ret.append(in, received);   
     }
    return (ret);
}

void     Network::writeServer(std::string msg)
{
    this->_socket.send(msg.c_str(), msg.size());
}

bool    Network::isReady(sf::Time timeout)
{
    if (this->_selector.wait(timeout))
    {
        if (this->_selector.isReady(this->_socket))
            return (true);
    }
    return (false);
}
