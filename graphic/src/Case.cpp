#include "Case.hpp"

DescRes::DescRes(sf::Vector2f pos, int type) {
  this->pos = pos;
  this->type = type;
}

Case::Case(float x, float y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystane)
{
    this->_ressources[FOOD] = food;
    this->_ressources[LINEMATE] = linemate;
    this->_ressources[DERAUMERE] = deraumere;
    this->_ressources[SIBUR] = sibur;
    this->_ressources[MENDIANE] = mendiane;
    this->_ressources[PHIRAS] = phiras;
    this->_ressources[THYSTAME] = thystane;

    this->_egg = false;

    this->_x = x;
    this->_y = y;

    for (int i = 0; i < NB_RESSOURCES; i++) {
      for (int n = 0; n < this->_ressources[i]; n++) {
        float x_var = (static_cast<float>(std::rand() % 8) / 10) - 0.3;
        float y_var = (static_cast<float>(std::rand() % 8) / 10) - 0.3;
        this->_resourcesPos[i].push_back(DescRes(sf::Vector2f(x + x_var, y + y_var), i));
      }
    }
}

Case::~Case()
{
}

int     Case::getItem(enum RESSOURCE it) const
{
    return (this->_ressources[it]);
}

void    Case::addRessource(enum RESSOURCE it, int nb)
{
    float x_var = (static_cast<float>(std::rand() % 8) / 10) - 0.3;
    float y_var = (static_cast<float>(std::rand() % 8) / 10) - 0.3;
    this->_resourcesPos[it].push_back(DescRes(sf::Vector2f(this->_x + x_var, this->_y + y_var), it));
    this->_ressources[it] += nb;
}

void    Case::delRessource(enum RESSOURCE it, int nb)
{
    if (!this->_resourcesPos[it].empty())
      this->_resourcesPos[it].pop_front();
    this->_ressources[it] -= nb;
}

 bool    Case::getEgg() const
{
     return (this->_egg);
}
 
 void    Case::setEgg(bool state)
 {

     this->_egg = state;
 }

 
 void    Case::addEgg(Egg *new_egg)
 {
     float x_var = (static_cast<float>(std::rand() % 8) / 10) - 0.3;
     float y_var = (static_cast<float>(std::rand() % 8) / 10) - 0.3;
     this->_eggsPos.push_back(DescRes(sf::Vector2f(this->_x + x_var, this->_y + y_var), 1 ) );
     this->_eggs.push_back(new_egg);
 }

void    Case::delEgg(std::string name)
{
    for (unsigned int i = 0; i < this->_eggs.size(); i++) {
        if (this->_eggs[i]->getNum() == name)
            {
                this->_eggs.erase(this->_eggs.begin() + i);
                if (!this->_eggsPos.empty())
                    this->_eggsPos.pop_front();
                break;
            }
    }
}

std::vector<Egg *> Case::getEggs() const
{
    return (this->_eggs);
}

void Case::setEggs(std::vector<Egg*> eggs)
{
    this->_eggs = eggs;
}

std::list<DescRes> Case::getAllResources() const {
  std::list<DescRes> allRes;

  for (int i = 0; i < NB_RESSOURCES; i++) {
    for (std::list<DescRes>::const_iterator it = this->_resourcesPos[i].begin(); it != this->_resourcesPos[i].end(); it++) {
      allRes.push_back(*it);
    }
  }
  return allRes;
}

std::list<DescRes> Case::getAllEggs() const {
    return (this->_eggsPos);    
}