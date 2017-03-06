#include <sstream>
#include "Content.hpp"

Content::Content(sf::RenderWindow *window, int x, int y)
{
    this->_window = window;
    this->_posX = x;
    this->_posY = y;
    
    this->_font.loadFromFile("graphic/media/sdl_files/KeepCalm.ttf");
    this->_display = false;
}

Content::~Content()
{
}

void Content::write_eggs(Case *elem, sf::Color color_font)
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getEggs().size(); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setColor(color_font);
    text.setPosition(this->_posX + 40, this->_posY + 44);
    this->_window->draw(text);
}

void Content::write_food(Case *elem, sf::Color color_font)
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getItem(static_cast<enum RESSOURCE>(0)); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(15);
    text.setColor(color_font);
    text.setPosition(this->_posX + 113, this->_posY + 80);
    this->_window->draw(text);
}

void Content::write_linemate(Case *elem, sf::Color color_font) //bleu
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getItem(static_cast<enum RESSOURCE>(1)); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(15);
    text.setColor(color_font);
    text.setPosition(this->_posX + 40, this->_posY + 105);
    this->_window->draw(text);
}

void Content::write_deraumere(Case *elem, sf::Color color_font) //violet
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getItem(static_cast<enum RESSOURCE>(4)); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(15);
    text.setColor(color_font);
    text.setPosition(this->_posX + 40, this->_posY + 130);
    this->_window->draw(text);
}

void Content::write_sibur(Case *elem, sf::Color color_font) //rouge
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getItem(static_cast<enum RESSOURCE>(2)); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(15);
    text.setColor(color_font);
    text.setPosition(this->_posX + 113, this->_posY + 105);
    this->_window->draw(text);
}

void Content::write_mendiane(Case *elem, sf::Color color_font) //vert
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getItem(static_cast<enum RESSOURCE>(5)); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(15);
    text.setColor(color_font);
    text.setPosition(this->_posX + 113, this->_posY + 130);
    this->_window->draw(text);
}

void Content::write_phiras(Case *elem, sf::Color color_font) //jaune
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getItem(static_cast<enum RESSOURCE>(3)); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(15);
    text.setColor(color_font);
    text.setPosition(this->_posX + 168, this->_posY + 106);
    this->_window->draw(text);
}

void Content::write_thystame(Case *elem, sf::Color color_font) //mauve
{
    std::string nb;
    std::ostringstream convert;
    convert << elem->getItem(static_cast<enum RESSOURCE>(6)); 
    nb = convert.str();
    
    sf::Text text(nb, this->_font);
    text.setCharacterSize(15);
    text.setColor(color_font);
    text.setPosition(this->_posX + 168, this->_posY + 131);
    this->_window->draw(text);
}

void Content::display_case(Case *elem, bool mask, sf::Color color_font)
{
    sf::Image image;
    
    if (this->_display == false)
        return;
   
    image.loadFromFile("graphic/media/sdl_files/details.png");
    if (mask)
        image.createMaskFromColor(sf::Color::Blue);    
    sf::Texture texture;
 	texture.loadFromImage(image);

    sf::Sprite sprite(texture);      
    
    sprite.setPosition(this->_posX, this->_posY);

    this->_window->draw(sprite);
    
    this->write_eggs(elem, color_font);
    this->write_food(elem, color_font);

    this->write_linemate(elem, color_font);
    this->write_deraumere(elem, color_font);
    this->write_sibur(elem, color_font);
    this->write_mendiane(elem, color_font);
    this->write_phiras(elem, color_font);
    this->write_thystame(elem, color_font);
}

void Content::display(bool disp)
{   
    this->_display = disp;
}