#ifndef CASE_HPP__
# define CASE_HPP__

# include <vector>
# include <list>
# include <SFML/Graphics.hpp>
# include "Egg.hpp"
# include "all_enum.h"

struct DescRes {
  DescRes(sf::Vector2f pos, int type);
  sf::Vector2f pos;
  int type;
};

class Case
{
    private:
    int     _ressources[NB_RESSOURCES];
    std::list<DescRes> _resourcesPos[NB_RESSOURCES];
    std::list<DescRes> _eggsPos;
    bool _egg;

    float _x;
    float _y;

  std::vector<Egg*> _eggs;

public:
    Case(float x, float y, int food = 0, int linemate = 0, int deraumere = 0, int sibur = 0, int mendiane = 0, int phiras = 0, int thystane = 0);
    ~Case();
    int     getItem(enum RESSOURCE it) const;
    void    addRessource(enum RESSOURCE it, int nb);
    void    delRessource(enum RESSOURCE it, int nb);
    void    addEgg(Egg *new_egg);
    void    delEgg(std::string name);
    bool    getEgg() const;
    void    setEgg(bool state);

  std::vector<Egg *> getEggs() const;
    void setEggs(std::vector<Egg*>);

    std::list<DescRes> getAllResources() const;
    std::list<DescRes> getAllEggs() const;
};

#endif /* !CASE_HPP__ */
