#ifndef RESUME_HPP
# define RESUME_HPP

# include <SFML/Graphics.hpp>
# include <vector>
# include <list>
# include "Player.hpp"

class Resume {
  public:

    Resume(sf::RenderWindow *, int, int);
    ~Resume();
    
    void display_resume(std::vector<Player*>);
    void setDisplay(bool);
    
    void setScroll(int);
    
    void writeInfos(Player *_player, int, int);

  private:
  
  void writeNames(Player *_player, int, int, sf::Font);
  void writeLevel(Player *_player, int, int, sf::Font);
  void writePos(Player *_player, int, int, sf::Font);
  void writeInventory(Player *_player, int, int, sf::Font);
  void writeDesc(int, int);


  private:
    
    sf::RenderWindow *_window;
    int _sizeMapX;
    int _sizeMapY;
    
    bool _display;
    
    int _scroll;
    
    sf::Font _fontk;
    
    std::vector<sf::Sprite > _ressources;
    
  };

# endif //RESUME_HPP
