#include <iostream>
#include "Log.hpp"

Log::Log(sf::RenderWindow *window, int posx, int posy, int width, int height)
{
    this->_window = window;
    this->_posX = posx;
    this->_posY = posy;
    this->_height = height;
    this->_width = width;
    this->_display = false;
}

Log::~Log()
{
}

void Log::write(std::string from, std::string msg, sf::Color color)
{
    unsigned int w = this->_width / 8;
    if (from.size() + msg.size() > w)
        {
            std::string new_msg;

            new_msg = msg.substr(0, w - from.size() - 2);
            msg = msg.substr(new_msg.size(), msg.size());
            this->write(from, new_msg, color);
            this->write("", msg, color);
            return;
        }
    this->_logs.push_back(msg);
    this->_colors.push_back(color);
    this->_from.push_back(from);
    
    unsigned int h = 15;

    if (this->_logs.size() > this->_height / h - 1)
    {
        this->_logs.erase(this->_logs.begin());
        this->_from.erase(this->_from.begin());
        this->_colors.erase(this->_colors.begin());
    }
    
}

void Log::display()
{
    if (this->_display == false)
        return;
    
    sf::Font font;
    font.loadFromFile("graphic/media/sdl_files/arial.ttf");

    for (unsigned int i = 0; i < this->_logs.size();i++) {

        sf::Text text(this->_from[i], font);
        text.setCharacterSize(15);
        text.setStyle(sf::Text::Bold);
        text.setColor(this->_colors[i]);
        text.setPosition(this->_posX + 10, this->_posY + (i * 15) + 10);
        this->_window->draw(text);
        
        sf::Text msg(this->_logs[i], font);
        msg.setCharacterSize(15);
        msg.setColor(sf::Color::White);
        msg.setPosition(this->_posX + (8 * this->_from[i].size()) + 10, this->_posY + (i * 15) + 10);
        this->_window->draw(msg);
        
    }

}

void Log::setDisplay()
{
    this->_display = (this->_display == false) ? true : false;
}