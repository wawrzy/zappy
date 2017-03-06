//
// Created by rottaf on 6/14/16.
//

#ifndef ZAPPY_GRAPHIC_ANIMATIONPLAYER_HH
#define ZAPPY_GRAPHIC_ANIMATIONPLAYER_HH


#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <list>
#include "Frame.hh"

namespace zappy {
  struct DescAnimation {
    DescAnimation(std::string const & name = "idle1", int speed = 120, bool loop = false);

    std::string const _name;
    int _speed;
    bool _loop;
  };

  enum ORIENTATION {
    NORTH = 3,
    SOUTH = 1,
    WEST = 2,
    EAST = 4
  };

  class AnimationPlayer {
  public:
    AnimationPlayer(sf::Sprite &sprite);

    ~AnimationPlayer();

  public:
    void setOrientation(ORIENTATION new_orientation);

  private:
    void _clean();

  public:
    void addMove(int speed = 80, bool loop = false);
    void addDie(int speed = 120, bool loop = false);
    void addIdle(int speed = 120, bool loop = true);
    void addPickUp(int speed = 120, bool loop = false);
    void addIncantation(int speed = 60, bool loop = true);

    void startMove(int speed = 80, bool loop = false);
    void startDie(int speed = 120, bool loop = false);
    void startIdle(int speed = 60, bool loop = true);
    void startPickUp(int speed = 120, bool loop = false);
    void startIncantation(int speed = 60, bool loop = true);

    void update(int tick);

    bool isAnimated() const;

  private:
    sf::Sprite &_sprite;
    Frame _frame;

    std::string _move;
    std::map<std::string, std::vector<int> > _indexAnimation;

    std::list<DescAnimation *> _queueAnimation;

    bool _animated;
  };
};

#endif //ZAPPY_GRAPHIC_ANIMATIONPLAYER_HH
