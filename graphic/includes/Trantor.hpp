#ifndef TRANTOR_HPP__
# define TRANTOR_HPP__

# include <string>
# include <SFML/Graphics.hpp>
# include <vector>
# include <map>
# include <MapTrantor.hh>
# include "Network.hpp"
# include "Case.hpp"
# include "Log.hpp"
# include "Player.hpp"

class Trantor
{
    private:
 
    Network *_socket;
    
    typedef int (Trantor::*cmd)(std::vector<std::string>);
    std::map<std::string, cmd> _commandList;

    MapTrantor _map;
    
    std::map<std::string, std::vector<Player*>> _teams;

    std::vector<Player*> _players;

    std::vector<Egg*> _eggs;

    bool mute;


    int     _tick;
    
    int _winX;
    int _winY;
    
    
    public:
    
    Trantor(std::string _server, int _port);
    ~Trantor();
    std::vector<std::string> parsCmd(std::string cmd);
    void initTrantorMap();
    int initLoadingImage(sf::RenderWindow *window);
    int core();
    int manageCmd(Log *logger);
    int initEndImage(sf::RenderWindow *window);

    int cmdMsz(std::vector<std::string>);
    int cmdBct(std::vector<std::string>);
    int cmdSgt(std::vector<std::string>);
    int cmdTna(std::vector<std::string>);
    int cmdPnw(std::vector<std::string>);
    int cmdPin(std::vector<std::string>);
    int cmdPlv(std::vector<std::string>);
    int cmdPpo(std::vector<std::string>);
    int cmdPex(std::vector<std::string>);
    int cmdPbc(std::vector<std::string>);
    int cmdPic(std::vector<std::string>);
    int cmdPie(std::vector<std::string>);
    int cmdPgt(std::vector<std::string>);
    int cmdPdi(std::vector<std::string>);
    int cmdEdi(std::vector<std::string>);
    int cmdEht(std::vector<std::string>);
    int cmdEnw(std::vector<std::string>);
    int cmdPfk(std::vector<std::string>);
    int cmdPdr(std::vector<std::string>);
    int cmdSeg(std::vector<std::string>);
    int cmdEbo(std::vector<std::string>);
};

#endif /* !TRANTOR_HPP__ */