//
// Created by rottaf on 6/20/16.
//

#ifndef ZAPPY_GRAPHIC_MAPTRANTOR_HH
#define ZAPPY_GRAPHIC_MAPTRANTOR_HH

#include <vector>
#include <Case.hpp>
#include <SFML/Graphics.hpp>

class MapTrantor {
public:
  MapTrantor();
  ~MapTrantor();

public:
  Case const * getCase(int x, int y) const;
  Case * getCase(int x, int y);
  void setCase(int x, int y, Case * newCase);

  std::vector<sf::Sprite *> const getAllSprites() const;

  std::list<sf::Sprite> const & getAllResourcesSprites();

  int getMaxX() const;
  void setMaxX(int x);

  int getMaxY() const;
  void setMaxY(int y);

  bool hasSizeMapChanged();

  int getOrigX() const;
  void setOrigX(int x);

  int getOrigY() const;
  void setOrigY(int x);

  sf::Texture const & getTexture() const;
  void setTexture(sf::Texture & texture);

private:
  void _cleanAll();
  void _resetPositionSprites();

public:
  void create(int x, int y);

  float getPixelX(float x, float y) const;
  float getPixelY(float x, float y) const;

  sf::Vector2i getPosFromPixel(int x, int y) const;

private:
  int _maxX;
  int _maxY;

  int _oldMaxX;
  int _oldMaxY;

  int _origX;
  int _origY;

  std::vector<Case *> _cases;
  std::vector<sf::Sprite *> _sprites;

  sf::Image _image;
  sf::Texture _texture;

  sf::Image _imageRes;
  sf::Texture _textureRes;

  sf::Image _imageEgg;
  sf::Texture _textureEgg;
  

  std::list<sf::Sprite> _spritesRes;
};


#endif //ZAPPY_GRAPHIC_MAPTRANTOR_HH
