#include "MiniMap.hpp"
#include "Case.hpp"

MiniMap::MiniMap(sf::RenderWindow *window, int x, int y, int width, int height)
{
    this->_posX = x;
    this->_posY = y;
    this->_width = width;
    this->_height = height;
    this->_window = window;
    this->_display = false;
}

MiniMap::~MiniMap()
{
}

#include <iostream>
void MiniMap::display(MapTrantor _map, std::vector<Player*> _players)
{
    if (this->_display == false)
        return;
    for (int x = 0; x < _map.getMaxX(); x++) {

        for (int y = 0; y < _map.getMaxY(); y++) {
            sf::Color color_case = sf::Color::Blue;
            for (unsigned int i = 0; i < _players.size(); i++) {
                if (_players[i]->getPosX() == x && _players[i]->getPosY() == y) {
                    color_case = sf::Color::Red;
                }
            }

             sf::RectangleShape rectangle1;
             rectangle1.setOutlineThickness(1);

             rectangle1.setSize(sf::Vector2f(this->_width / _map.getMaxX(), this->_height / _map.getMaxY()));
             
             rectangle1.setPosition(this->_posX + this->_width - (x * (this->_width / _map.getMaxX()) ) - 20, this->_posY + (this->_height) - (y * (this->_height / _map.getMaxY()) ) - (this->_height / _map.getMaxY() ) );
             

             rectangle1.setFillColor(sf::Color::Black);             
             rectangle1.setOutlineColor(sf::Color::Green);
             
             if (color_case == sf::Color::Red)
                rectangle1.setFillColor(color_case);
             
             this->_window->draw(rectangle1);
           
        }
    }
}

void MiniMap::setDisplay()
{
    this->_display = (this->_display == false) ? true : false;
}