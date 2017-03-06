/*
** Trantor.cpp for Trantor in /home/wawrzy-j/Documents/Projets/PSU/PSU_2015_zappy/graphic/src
**
** Made by wawrzy-j
** Login   <wawrzy-j@wawrzy-j>
**
** Started on  Mon Jun 13 18:06:44 2016 wawrzy-j
** Last update Mon Jun 13 18:06:46 2016 wawrzy-j
*/

#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <unistd.h>
#include <SFML/Audio.hpp>
#include "Trantor.hpp"
#include "Content.hpp"
#include "Color.hpp"
#include "Error.hpp"
#include "Resume.hpp"
#include "MiniMap.hpp"

bool compareSpriteY(sf::Sprite const & sp1, sf::Sprite const & sp2) {
  return sp1.getPosition().y > sp2.getPosition().y;
}

Trantor::Trantor(std::string _server, int _port)
{
    this->_winX = 1024;
    this->_winY = 768;

    this->mute = false;
    
    this->_tick = 0;

    this->_socket = new Network(_server, _port);
    
    this->_commandList["msz"] = &Trantor::cmdMsz;
    this->_commandList["bct"] = &Trantor::cmdBct;
    this->_commandList["sgt"] = &Trantor::cmdSgt;
    this->_commandList["tna"] = &Trantor::cmdTna;
    this->_commandList["pnw"] = &Trantor::cmdPnw;
    this->_commandList["pin"] = &Trantor::cmdPin;
    this->_commandList["plv"] = &Trantor::cmdPlv;
    this->_commandList["ppo"] = &Trantor::cmdPpo;
    this->_commandList["pex"] = &Trantor::cmdPex;
    this->_commandList["pbc"] = &Trantor::cmdPbc;
    this->_commandList["pic"] = &Trantor::cmdPic;
    this->_commandList["pie"] = &Trantor::cmdPie;
    this->_commandList["pgt"] = &Trantor::cmdPgt;
    this->_commandList["pdi"] = &Trantor::cmdPdi;

    this->_commandList["edi"] = &Trantor::cmdEdi;
    this->_commandList["ebo"] = &Trantor::cmdEbo;    

    this->_commandList["eht"] = &Trantor::cmdEht;
    this->_commandList["enw"] = &Trantor::cmdEnw;
    this->_commandList["pfk"] = &Trantor::cmdPfk;
    this->_commandList["pdr"] = &Trantor::cmdPdr;
    
     this->_commandList["seg"] = &Trantor::cmdSeg;

}

Trantor::~Trantor()
{
    delete this->_socket;
    std::cout << GREEN  << "CLEAN" << NOT << std::endl;
}

std::vector<std::string> Trantor::parsCmd(std::string cmd)
{
    std::string arg;    
    std::vector<std::string> args;
    
    std::istringstream iss(cmd);
 
    std::getline(iss, arg, ' ');
    while (!arg.empty())
    {
       args.push_back(arg);
       arg.erase();
       std::getline(iss, arg, ' ');
    }
    
    return (args);
}

int Trantor::initEndImage(sf::RenderWindow *window)
{
    
    window->close();

    return (0);
}

int Trantor::initLoadingImage(sf::RenderWindow *window)
{
    sf::Texture menuTexture;
    if (menuTexture.loadFromFile("graphic/media/sdl_files/loading.jpg") == false)
        return (1);

    sf::Sprite sprite(menuTexture);

    window->clear();
    window->draw(sprite);
    window->display();
    
    return (0);
}

void Trantor::initTrantorMap()
{
    this->_socket->writeServer("GRAPHIC\n");
    std::vector<std::string> args;
    sf::Time time = sf::seconds(0.2f);

    bool dim = false;
    bool tick = false;
    bool map = false;
    bool team = false;
    
    while (this->_socket->isReady(time))
    {
      args = this->parsCmd(this->_socket->readServerLine());
      if (args[0] == "msz")
        dim = true;
      else if (args[0] == "sgt")
        tick = true;
      else if (args[0] == "bct")
        map = true;
      else if (args[0] == "tna")
        team = true;
      std::cout << args[0] << std::endl;
      if (args.size() == 0 || !(this->_commandList[args[0].c_str()]))
        throw Error("Bad server answer");
      (this->*this->_commandList[args[0].c_str()])(args);
      if (dim && tick && map && team && args[0] != "tna")
        break;
    }

    if (!dim || !tick || !map || !team)
        throw Error("Bad server answer");
}

int Trantor::manageCmd(Log *logger)
{
    std::string cmd;

    cmd = this->_socket->readServerLine();
     logger->write("Server :", cmd, sf::Color::Red);
    std::cout << BLUE << cmd << NOT << std::endl;
    if (cmd.empty())
    {
        std::cout << "SOCKET CLOSED" << std::endl;
        return (1);
    }
    std::vector<std::string> args = this->parsCmd(cmd);
    if (this->_commandList[args[0].c_str()])
    {
        if ((this->*this->_commandList[args[0].c_str()])(args) != 1)
            {
               if (args[0] == "pbc")
                   logger->write("Broadcast :", args[2], sf::Color::Green);
            }
    }
    
    else
        std::cerr << RED << "ERROR COMMAND :" << cmd << std::endl;
    return (0);
}

int Trantor::core()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1024, 768), "EZ Zappy");

    if (this->initLoadingImage(window) == 1)
        return (1);

    try {
       this->_socket->initSocket();
       this->initTrantorMap();
     } catch (Error &e) {
       std::cerr << e.what() << std::endl;
       return (1);
    }

    window->close();
    window->create(sf::VideoMode(1040, 720), "EZ");

    int ret;

    std::cout << GREEN << "START" << NOT << std::endl;

    sf::Color color(58, 212, 223);

    int tick = 0;

    Log *logger = new Log(window, 0, 0, 200, 250);
    Content cont_case(window, 0, 500);
    sf::Vector2i pos;
    MiniMap _minimap(window, 1040 - (this->_map.getMaxX() * 5), 0, this->_map.getMaxX() * 5, this->_map.getMaxY() * 5);
    Resume _resume(window, 1040, 720);
    int focus_player = -1;
    sf::Vector2i sizeMap;

    sf::Music music;
    music.openFromFile("graphic/media/Jacob - Hofmann.ogg");
    music.setLoop(true);
    music.play();

    sf::Font font;
    font.loadFromFile("graphic/media/sdl_files/KeepCalm.ttf");

    while (window->isOpen()) {

      sf::Event event;
      while (window->pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window->close();
        if (focus_player == -1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          this->_map.setOrigY(this->_map.getOrigY() - 20);
        }
        if (focus_player == -1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          this->_map.setOrigY(this->_map.getOrigY() + 20);
        }
        if (focus_player == -1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          this->_map.setOrigX(this->_map.getOrigX() - 20);
        }
        if (focus_player == -1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          this->_map.setOrigX(this->_map.getOrigX() + 20);
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::M)) {
          _minimap.setDisplay();
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::L)) {
          logger->setDisplay();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
          bool selection_player = false;
          for (unsigned int index_player = 0; index_player < this->_players.size() && !selection_player; index_player++) {
            const sf::Sprite sprite_player = this->_players[index_player]->getSprite();
            if (localPosition.x >= sprite_player.getPosition().x &&
                localPosition.x < (sprite_player.getPosition().x + sprite_player.getTextureRect().width) &&
                localPosition.y >= sprite_player.getPosition().y &&
                localPosition.y < (sprite_player.getPosition().y + sprite_player.getTextureRect().height)) {
              selection_player = true;
              focus_player = index_player;
            }
          }
          if (!selection_player) {
            pos = this->_map.getPosFromPixel(localPosition.x, localPosition.y);
            if (pos.x != -1 && pos.y != -1) {
              cont_case.display(true);
            }
            else {
              cont_case.display(false);
            }
          }
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::C)) {
          cont_case.display(false);
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
          focus_player = -1;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab) {
            _resume.setDisplay(true);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tab) {
            _resume.setDisplay(false);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::PageUp) {
            _resume.setScroll(-1);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::PageDown) {
            _resume.setScroll(1);
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
          this->mute = !this->mute;
          music.setVolume((this->mute ? 0 : 100));
          for (unsigned int i = 0; i < this->_players.size(); i++) {
            this->_players[i]->getBroadcastSound().setVolume((this->mute ? 0 : MAX_VOLUME_MURLOC));
          }
        }
      }

      if (focus_player != -1) {
        sf::Vector2i center_player;
        sf::Sprite const sprite_player = this->_players[focus_player]->getSprite();
        center_player.x = (sprite_player.getPosition().x * 2 + sprite_player.getTextureRect().width) / 2;
        center_player.y = (sprite_player.getPosition().y * 2 + sprite_player.getTextureRect().height) / 2;
        this->_map.setOrigX(this->_map.getOrigX() - (center_player.x - (window->getSize().x / 2)));
        this->_map.setOrigY(this->_map.getOrigY() - (center_player.y - (window->getSize().y / 2)));
      }
      if (this->_map.hasSizeMapChanged() && this->_map.getMaxX() != 0 && this->_map.getMaxY() != 0) {
        this->_map.setOrigX(this->_map.getOrigX() - (this->_map.getPixelX((this->_map.getMaxX() - 1) / 2, (this->_map.getMaxY() - 1) / 2) - (window->getSize().x / 2)));
        this->_map.setOrigY(this->_map.getOrigY() - (this->_map.getPixelY((this->_map.getMaxX() - 1) / 2, (this->_map.getMaxY() - 1) / 2) - (window->getSize().y / 2)));
      }
      if (!window->isOpen())
        break;

        tick += 1;

        for (unsigned int i = 0; i < this->_players.size(); i++) {
            if (! this->_players[i]->isAlive() && ! this->_players[i]->getAnim().isAnimated()) {
              this->_players.erase(this->_players.begin() + i);
              i -= 1;
            }
            else {
              this->_players[i]->update(tick);
            }
        }


        window->clear();

        std::vector<sf::Sprite *> tabCase = this->_map.getAllSprites();
        for (unsigned int i = 0; i < tabCase.size(); i++) {
            window->draw(*tabCase[i]);
        }
      
        std::list<sf::Sprite> const spritesRes = this->_map.getAllResourcesSprites();
        for (std::list<sf::Sprite>::const_iterator it = spritesRes.begin(); it != spritesRes.end(); it++) {
          window->draw(*it);
        }

        for (unsigned int i = 0; i < this->_players.size(); i++) {
          window->draw(this->_players[i]->getSprite());;


          const sf::Sprite sprite_player = this->_players[i]->getSprite();
          sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
          if ((localPosition.x >= sprite_player.getPosition().x &&
               localPosition.x < (sprite_player.getPosition().x + sprite_player.getTextureRect().width) &&
               localPosition.y >= sprite_player.getPosition().y &&
               localPosition.y < (sprite_player.getPosition().y + sprite_player.getTextureRect().height))) {
              sf::Text text(this->_players[i]->getName(), font);
              text.setCharacterSize(20);
              text.setStyle(sf::Text::Bold);
              text.setColor(sf::Color::White);
              sf::Sprite const sprite = this->_players[i]->getSprite();
              text.setPosition(this->_players[i]->getSprite().getPosition().x + sprite.getTextureRect().width / 2 - text.getLocalBounds().width / 2, sprite.getPosition().y + sprite.getTextureRect().height );
              std::ostringstream os;
              os << this->_players[i]->getLevel();
              sf::Text text2;
              text2.setFont(font);
              text2.setCharacterSize(20);
              text2.setStyle(sf::Text::Bold);
              text2.setColor(sf::Color::White);
              text2.setString(this->_players[i]->getTeam() + " (" + os.str() + ")");
              text2.setPosition(this->_players[i]->getSprite().getPosition().x + sprite.getTextureRect().width / 2 - text2.getLocalBounds().width / 2, sprite.getPosition().y + sprite.getTextureRect().height + text.getLocalBounds().height);
              sf::RectangleShape backgroundText;
              backgroundText.setSize(sf::Vector2f(text2.getLocalBounds().width + 7, text2.getLocalBounds().height + text.getLocalBounds().height + 7));
              backgroundText.setFillColor(sf::Color(48, 48, 48, 255));
              backgroundText.setOutlineColor(sf::Color(0, 255, 248, 255));
              backgroundText.setOutlineThickness(2);
              backgroundText.setPosition(this->_players[i]->getSprite().getPosition().x + sprite.getTextureRect().width / 2 - backgroundText.getSize().x / 2, sprite.getPosition().y + sprite.getTextureRect().height);
              window->draw(backgroundText);
              window->draw(text);
              window->draw(text2);
            }          
          
          if (this->_players[i]->isBroadcasting()) {
            window->draw(this->_players[i]->getBroadcastSprite());
          }
        }

        logger->display();
        _minimap.display(this->_map, this->_players);
        cont_case.display_case(this->_map.getCase(pos.x, pos.y), true,  sf::Color::White);
        _resume.display_resume(this->_players);

        window->display();

        int _nbcmd = 0;
        while (this->_socket->isReady() && _nbcmd < 10)
        {
            ret = this->manageCmd(logger);
            if (ret == 1)
                {
                    window->close();
                    delete window;
                    return (1);
                }
            else if (ret == -2)
                {
                   return (0);
                }    
            _nbcmd += 1    ;        
        }
        

    }
    

    this->initEndImage(window);
    delete window;
    return (0);
}