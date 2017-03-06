#include "Egg.hpp"

Egg::Egg(std::string num, int x, int y)
{
    this->_num = num;
    this->_status = false;
    this->_x = x;
    this->_y = y;
}

Egg::~Egg()
{
}

std::string Egg::getNum() const
{
    return (this->_num);
}

bool Egg::getStatus() const
{
    return (this->_status);
}

void Egg::setStatus(bool status)
{
    this->_status = status;
}

int Egg::getPosX() const
{
    return (this->_x);
}

int Egg::getPosY() const
{
    return (this->_y);
}
    