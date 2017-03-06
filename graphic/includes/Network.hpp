#ifndef NETWORK_HPP__
# define NETWORK_HPP__

# include <string>
# include <SFML/Network.hpp>

class Network
{
    private:
    
    int _port;
    std::string _server;
    sf::SocketSelector _selector;    
    sf::TcpSocket _socket;
        
    public:
    
    Network(std::string _ip, int _port);
    ~Network();
    
    void    initSocket();
    void     writeServer(std::string msg);
    std::string   readServerLine();
    std::string   readServer();
    bool        isReady(sf::Time timeout=sf::seconds(0.01f));
    
};

#endif /* !NETWORK_HPP__ */