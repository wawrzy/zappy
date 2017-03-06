#ifndef MINIMAP_HPP__
# define MINIMAP_HPP__

# include <vector>
# include "MapTrantor.hh"
# include "Player.hpp"

class MiniMap
{
  private:
  
  int _posX;
  int _posY;
  int _width;
  int _height;
  
  bool _display;
  
  sf::RenderWindow *_window;
  
  public:
  MiniMap(sf::RenderWindow *window, int x, int y, int width, int height);
  ~MiniMap();
  void display(MapTrantor _map, std::vector<Player*> _players);
  void setDisplay();
  
};

#endif /* !MINIMAP_HPP__ */