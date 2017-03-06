#ifndef PLAYER_HPP__
# define PLAYER_HPP__

# include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <AnimationPlayer.hh>
#include <MapTrantor.hh>
#include "all_enum.h"

# define ABS(X) (((X < 0) ? (X * (-1)) : X))

enum ORIENTATION
  {
    NORTH,
    OST,
    SOUTH,
    WEST
  };

# define MAX_VOLUME_MURLOC (20)

class Player
{
private:
  std::string _name;
  std::string _team;
  zappy::ORIENTATION _orientation;
  int     _oldlevel;
  int     _level;
  int     _y;
  int     _x;
  int _inventory[7];
  bool _incantation;
  bool _fork;

  zappy::AnimationPlayer _anim;
  float     _oldX;
  float     _oldY;
  int     _maxX;
  int     _maxY;
  int     _lastTick;
  int     _startTick;
  enum ORIENTATION _newOrientation;
  sf::Sprite _sprite;
  std::vector<sf::Texture> _texture;
  std::vector<sf::Image> _image;
  int _timeToMove;

  int _tickLeftBroadcast;
  sf::Sprite _spriteBroadcast;
  sf::Texture _textureBroadcast;
  sf::Image _imageBroadcast;

  sf::SoundBuffer _soundBufferBroadcast;
  sf::Sound _soundBroadcast;

  MapTrantor const & _map;

  bool alive;

private:
  float getPixelX(float x, float y);
  float getPixelY(float x, float y);
  float _updateX();
  float _updateY();
  float _getDistance();
  void _updateBroadcast();

public:
  Player(std::string name, std::string team, zappy::ORIENTATION orientation, int level, int x, int y, MapTrantor const & map);
  ~Player();
  std::string getName() const;
  std::string getTeam() const;
  zappy::ORIENTATION getOrientation() const;
  void setOrientation(zappy::ORIENTATION orientation);
  int getRessource(enum RESSOURCE id);
  void addRessource(enum RESSOURCE it, int nb);
  void delRessource(enum RESSOURCE it, int nb);
  void setLevel(int level);
  void setPos(int x, int y);
  void moveTo(int x, int y, zappy::ORIENTATION orientation);
  int getLevel() const;
  int getPosX() const;
  int getPosY() const;
  void setIncantation(bool status);
  bool getIncantation() const;
  void setFork(bool status);
  bool getFork() const;

  void activeBroadcast(int tick = 80);
  bool isBroadcasting() const;
  sf::Sprite const & getBroadcastSprite();
  sf::Sound & getBroadcastSound();

  zappy::AnimationPlayer const & getAnim() const;
  zappy::AnimationPlayer & getAnim();

  bool isAlive() const;
  void kill();

  sf::Sprite const & getSprite() const;

public:
  void update(int tick);
};

#endif /* !PLAYER_HPP__ */
