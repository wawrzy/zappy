#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include "Trantor.hpp"
#include "Color.hpp"
#include "Error.hpp"

int Trantor::cmdPdr(std::vector<std::string> args)
{
    if (args.size() != 3)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    
    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    int item = std::stoi(args[2]);

    if (item < 0 || item > 6)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    if ( this->_players[i]->getRessource(static_cast<enum RESSOURCE>(item)) == 0 )
        return (0);
    
    this->_players[i]->delRessource(static_cast<enum RESSOURCE>(item), 1);
    this->_players[i]->getAnim().startPickUp();
    this->_map.getCase(this->_players[i]->getPosX(), this->_players[i]->getPosY())->addRessource(static_cast<enum RESSOURCE>(item), 1);
    
    return (0);
}

int Trantor::cmdEdi(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    bool check = false;
    unsigned int i = 0;
    while (i < this->_eggs.size())
    {
        if (this->_eggs[i]->getNum() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Egg doesn't exist" <<  std::endl;
        return (1);
    }

    this->_map.getCase(this->_eggs[i]->getPosX(), this->_eggs[i]->getPosY())->delEgg(args[1]);
    this->_eggs.erase(this->_eggs.begin() + i);
    return (0);
}

int Trantor::cmdEbo(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    bool check = false;
    unsigned int i = 0;
    while (i < this->_eggs.size())
    {
        if (this->_eggs[i]->getNum() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Egg doesn't exist" <<  std::endl;
        return (1);
    }
    
    
    this->_map.getCase(this->_eggs[i]->getPosX(), this->_eggs[i]->getPosY())->delEgg(args[1]);
    this->_eggs.erase(this->_eggs.begin() + i);
     // CONNECTION PLAYER FOR EGG
    return (0);
}

int Trantor::cmdEht(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    bool check = false;
    unsigned int i = 0;
    while (i < this->_eggs.size())
    {
        if (this->_eggs[i]->getNum() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Egg doesn't exist" <<  std::endl;
        return (1);
    }

    // ANIMATION ECLOSION
    this->_eggs[i]->setStatus(true);
    this->_map.getCase(this->_eggs[i]->getPosX(), this->_eggs[i]->getPosY())->delEgg(args[1]);
    this->_eggs.erase(this->_eggs.begin() + i);
    return (0);
}

int Trantor::cmdEnw(std::vector<std::string> args)
{
    if (args.size() != 5)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[2])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    this->_players[i]->setFork(false);
    Egg *new_egg = new Egg(args[1], this->_players[i]->getPosX(), this->_players[i]->getPosY());

    this->_eggs.push_back(new_egg);

    this->_map.getCase(this->_players[i]->getPosX(), this->_players[i]->getPosY())->addEgg(new_egg);
    
    return (0);
}

int Trantor::cmdPfk(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    this->_players[i]->setFork(true);
    return (0);
}

int Trantor::cmdPdi(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }

    for (unsigned int j = 0; j < this->_teams[this->_players[i]->getTeam().c_str()].size(); j++) {
        if (this->_teams[this->_players[i]->getTeam().c_str()][j]->getName() == this->_players[i]->getName())
            {
                this->_teams[this->_players[i]->getTeam().c_str()].erase(this->_teams[this->_players[i]->getTeam().c_str()].begin() + j);
                break;
            }
    }

    this->_players[i]->getAnim().startDie();
    this->_players[i]->kill();

    return (0);
}

int Trantor::cmdPgt(std::vector<std::string> args)
{
    if (args.size() != 3)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    
    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    int item = std::stoi(args[2]);

    if (item < 0 || item > 6)
    {
        std::cerr << RED << "Bad command : " << NOT << "Item doesn't exist" <<  std::endl;
        return (1);
    }

    if ( this->_map.getCase(this->_players[i]->getPosX(), this->_players[i]->getPosY())->getItem(static_cast<enum RESSOURCE>(item))  == 0)
        return (0);
    this->_players[i]->addRessource(static_cast<enum RESSOURCE>(item), 1);
    this->_players[i]->getAnim().startPickUp();
    this->_map.getCase(this->_players[i]->getPosX(), this->_players[i]->getPosY())->delRessource(static_cast<enum RESSOURCE>(item), 1);
    
    return (0);
}

int Trantor::cmdPie(std::vector<std::string> args)
{
    if (args.size() < 4)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    
    std::vector<Player*> players;
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    for (unsigned int i = 0; i < this->_players.size(); i++) {
        if (this->_players[i]->getPosX() == x && this->_players[i]->getPosY() == y)
            players.push_back(this->_players[i]);
    }

    for (unsigned int i = 0; i < players.size(); i++) {
        if (players[i]->getIncantation() == true)
        {
            // END ANIMATION INCANT (FAIL OR NOT)
            players[i]->setIncantation(false);
            this->_players[i]->getAnim().startIdle();
        }
    }
    return (0);
}

int Trantor::cmdPic(std::vector<std::string> args)
{
    if (args.size() < 5)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    for (unsigned int i = 4; i < args.size(); i++) {
        for (unsigned int j = 0; j < this->_players.size(); j++) {
            if (this->_players[j]->getName() == args[i])
                {
                    // ANIMATION INCANT ?
                    this->_players[j]->setIncantation(true);
                    this->_players[j]->getAnim().startIncantation();
                }
        }
    }
    return (0);   
}

int Trantor::cmdPbc(std::vector<std::string> args)
{
    if (args.size() < 3)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    
    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    // ANIMATION BROADCAST ?
    this->_players[i]->activeBroadcast();
    
    return (0);
}

int Trantor::cmdPex(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    // ANIMATION EXPULSE ?
    return (0);
}

int Trantor::cmdPpo(std::vector<std::string> args)
{
    if (args.size() != 5)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    
    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }

    this->_players[i]->moveTo(std::stoi(args[2]), std::stoi(args[3]), static_cast<zappy::ORIENTATION>(std::stoi(args[4])));
    return (0);
}

int Trantor::cmdPlv(std::vector<std::string> args)
{
   if (args.size() != 3)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    this->_players[i]->setLevel(std::stoi(args[2]));
    
    int max = 0;
    std::string name;
    for (unsigned int i = 0; i < this->_players.size(); i++) {
        if (this->_players[i]->getLevel() > max)
        {
            max = this->_players[i]->getLevel();
            name = this->_players[i]->getTeam();
            std::cout << RED << "LVL MAX = " << max << " TEAM = " << name << std::endl;
        }        
    }
    
    return (0);
}

int Trantor::cmdPin(std::vector<std::string> args)
{
    if (args.size() != 11)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    bool check = false;
    unsigned int i = 0;
    while (i < this->_players.size())
    {
        if (this->_players[i]->getName() == args[1])
        {
            check = true;
            break;
        }
        i++;
    }
    if (!check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player doesn't exist" <<  std::endl;
        return (1);
    }
    
    for (int j = 4; j < 11; j++) {
         this->_players[i]->addRessource(static_cast<enum RESSOURCE>(j - 4),
                                         -(this->_players[i]->getRessource(static_cast<enum RESSOURCE>(j - 4))));
        this->_players[i]->addRessource(static_cast<enum RESSOURCE>(j - 4),
                                        std::stoi(args[j]));
    }
    
    return (0);    
}

int Trantor::cmdPnw(std::vector<std::string> args)
{
    if (args.size() != 7)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    
    bool check = false;
    for (unsigned int i = 0; i < this->_players.size(); i++) {
        if (this->_players[i]->getName() == args[1])
            check = true;
    }    
    if (check)
    {
        std::cerr << RED << "Bad command : " << NOT << "Player already exist" <<  std::endl;
        return (1);
    }
    check = false;
    
    if (this->_teams.find(args[6]) == this->_teams.end())
    {
        std::cerr << RED << "Bad command : " << NOT << "Tean doesn't exist" <<  std::endl;
        return (1);
    }

    Player *new_player = new Player(args[1], 
                                    args[6],
                                    static_cast<zappy::ORIENTATION>(std::stoi(args[4])),
                                    std::stoi(args[5]),
                                    std::stoi(args[2]),
                                    std::stoi(args[3]),
                                    this->_map);
    new_player->getBroadcastSound().setVolume((this->mute ? 0 : MAX_VOLUME_MURLOC));
    this->_players.push_back(new_player);
    new_player->setOrientation(static_cast<zappy::ORIENTATION>(std::stoi(args[4])));
    this->_teams[new_player->getTeam().c_str()].push_back(new_player);
    
    return (0);
}

int Trantor::cmdMsz(std::vector<std::string> args)
{
    if (args.size() != 3)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    int _sizeMapX = std::stoi(args[1]);
    int _sizeMapY = std::stoi(args[2]);

    this->_map.create(_sizeMapX, _sizeMapY);
    
    return (0);
}

int Trantor::cmdSgt(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    this->_tick = std::stoi(args[1]);
    return (0);
}

int Trantor::cmdBct(std::vector<std::string> args)
{
    if (args.size() != 10)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    if (this->_map.getMaxX() <= std::stoi(args[1]) || this->_map.getMaxY() <= std::stoi(args[2]))
    {
        std::cerr << RED << "Bad command : " << NOT << "Index out of range (BCT)" <<  std::endl;
        return (1);
    }
    
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    
    if (x < 0 || y < 0)
        return (0);
    
    Case *elem = this->_map.getCase(x, y);
    
    for (int i = 3; i < 10; i++) {
        
        if (elem->getItem(static_cast<enum RESSOURCE>(i - 3)) != std::stoi(args[i]) )
        {

            int diff = std::stoi(args[i]) - elem->getItem(static_cast<enum RESSOURCE>(i - 3));

            if (diff > 0)
                for (int j = 0; j < diff; j++) {
                elem->addRessource(static_cast<enum RESSOURCE>(i - 3), 1);
                }
            else
            {
                for (int j = 0; j < (diff * -1); j++ ) {
                elem->delRessource(static_cast<enum RESSOURCE>(i - 3), 1);

                if (elem->getItem(static_cast<enum RESSOURCE>(i - 3)) == -1)
                    elem->addRessource(static_cast<enum RESSOURCE>(i - 3), 1);

                }
            }

        }
        
    }
    
    return (0);
}

int Trantor::cmdTna(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }
    if (this->_teams.find(args[1]) == this->_teams.end())
    {
        std::vector<Player*> players;
        this->_teams[args[1]] = players;
    }
    else
    {
        std::cerr << RED << "Bad command : " << NOT << "Team already exist !" <<  std::endl;
        return (1);
    }
    return (0);
}

int Trantor::cmdSeg(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        std::cerr << RED << "Bad command : " << NOT << args[0] <<  std::endl;
        return (1);
    }

    return (-2);
}