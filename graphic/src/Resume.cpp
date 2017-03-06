#include <sstream>
#include "Resume.hpp"
#include <iostream>
#include <unistd.h>
Resume::Resume(sf::RenderWindow *window, int sizex, int sizey)
{
    this->_window = window;
    this->_sizeMapX = sizex;
    this->_sizeMapY = sizey;
    this->_display = false;
    this->_scroll = 0;

    this->_fontk.loadFromFile("graphic/media/sdl_files/KeepCalm.ttf");;
    
}

Resume::~Resume()
{
}

void Resume::writeInventory(Player *_player, int x, int y, sf::Font font)
{
    int r = 0;
    x += 290;

    sf::Image _imageRes;
    _imageRes.loadFromFile("graphic/media/sdl_files/resources.bmp");
    _imageRes.createMaskFromColor(sf::Color::Blue);

    sf::Texture texture;
    texture.loadFromImage(_imageRes);
    
    int decal = _imageRes.getSize().x / 7;

    int posx = 0;

    sf::Texture t;
    t.loadFromImage(_imageRes);

    this->_ressources.clear();
        
    for (int i = 0; i < 7; i++) {
        sf::Sprite sprite;
        sprite.setTexture(t);
        sprite.setTextureRect(sf::IntRect(posx, 0, decal, texture.getSize().y));
        this->_ressources.push_back(sprite);
        posx += decal;
    }
    
    for (int i = 0; i < 7; i++) {
            std::string nb;
        std::ostringstream convert;
        convert << _player->getRessource(static_cast<enum RESSOURCE>(i) ); 
        nb = convert.str();
        
        sf::Sprite rec = this->_ressources[i];
        
        rec.setPosition(x, y);
        
        this->_window->draw(rec);
        
        sf::Text text(nb, font);
        text.setCharacterSize(14);
        text.setColor(sf::Color::Black);
        text.setPosition(x + 21, y);
        this->_window->draw(text); 
        
        x += 40;
        r++;
    }
}

void Resume::writeNames(Player *_player, int x, int y, sf::Font font)
{

    
    sf::Text text(_player->getName(), font);
    text.setCharacterSize(15);
    text.setColor(sf::Color::Black);
    text.setPosition(x, y);
    this->_window->draw(text);   
    
    std::string team;
    std::string team_str = _player->getTeam();
    if (team_str.size() >= 10)
        for (int i = 0; i < 10; i++) {
            team.append(1, team_str[i]);
        }
    else
        team = team_str;
    
    sf::Text text1(team, font);
    text1.setCharacterSize(15);
    text1.setColor(sf::Color::White);
    text1.setPosition(x + 100, y);
    this->_window->draw(text1);
}

void Resume::writeLevel(Player *_player, int x, int y, sf::Font font)
{
    std::string nb;
    std::ostringstream convert;
    convert << _player->getLevel(); 
    nb = convert.str();
    
    sf::Text text(nb, font);
    text.setCharacterSize(15);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(x + 200, y);
    this->_window->draw(text);   
    
}

void Resume::writePos(Player *_player, int x, int y, sf::Font font)
{
    std::string nb;
    std::ostringstream convert;
    convert << _player->getPosX(); 
    nb = convert.str();
    
    sf::Text text(nb, font);
    text.setCharacterSize(15);
    text.setColor(sf::Color::Blue);
    text.setPosition(x + 230, y);
    this->_window->draw(text);   
    
    std::ostringstream convert1;
    convert1 << _player->getPosY(); 
    nb = convert1.str();
    
    sf::Text text1(nb, font);
    text1.setCharacterSize(15);
    text1.setColor(sf::Color::Blue);
    text1.setPosition(x + 260, y);
    this->_window->draw(text1);   
    
}

void Resume::writeDesc(int x, int y)
{
    sf::Font font = this->_fontk;

    sf::RectangleShape rectangle;
     
    rectangle.setSize(sf::Vector2f(this->_sizeMapX / 4 * 2 + 50, 20) );

    rectangle.setPosition(this->_sizeMapX / 4, y);
    rectangle.setFillColor(sf::Color(0, 255, 0, 220));
     
     this->_window->draw(rectangle);
    
    sf::Text text("Player         Team      Level   Pos      Inventory", font);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    text.setPosition(x, y);
    this->_window->draw(text);
}

void Resume::writeInfos(Player *_player, int x, int y)
{
    sf::Font font = this->_fontk;

    this->writeNames(_player, x, y, font);
    this->writeLevel(_player, x, y, font);
    this->writePos(_player, x, y, font);
    this->writeInventory(_player, x, y, font);
 
}

void Resume::display_resume(std::vector<Player*> _players)
{
    if (_display == false)
        return;

     int nb = _players.size();

     int y = this->_sizeMapY / 2 - (20 * (nb / 2));
    
     sf::Color color1(86, 115, 154, 250);
     sf::Color color2(127, 143, 166, 250);

     int scroll = 0;
     if (nb > 15)
     {
        scroll = this->_scroll;  
        if (nb - scroll < 15)
        {
            scroll = nb - 15;
            this->_scroll = scroll;
        }
     }
     int start = scroll;

    this->writeDesc(this->_sizeMapX / 4, y - 20);
     
     for (int i = scroll; i < scroll + nb ; i++) {

     if (i - start > 15 || i >= static_cast<int>(_players.size()) )
        break;

     sf::Color color = color1;
     if (i % 2 == 0)
        color = color2;
     
     sf::RectangleShape rectangle;
     
     rectangle.setSize(sf::Vector2f(this->_sizeMapX / 4 * 2 + 50, 20) );

     rectangle.setPosition(this->_sizeMapX / 4, y);
     rectangle.setFillColor(color);
     
     this->_window->draw(rectangle);
     
     
     this->writeInfos(_players[i], this->_sizeMapX / 4, y);

     y += 20;
     
     }
}

void Resume::setDisplay(bool st)
{
    this->_display = st;
}

void Resume::setScroll(int scroll)
{
    this->_scroll += scroll;
    if (this->_scroll < 0)
        this->_scroll = 0;
}