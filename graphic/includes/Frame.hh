//
// Created by rottaf on 6/14/16.
//

#ifndef ZAPPY_GRAPHIC_FRAME_HH
#define ZAPPY_GRAPHIC_FRAME_HH

#include <SFML/Graphics/Rect.hpp>

namespace zappy {
  class Frame {
  public:
    Frame();
    ~Frame();

  public:
    sf::IntRect const getSubRect() const;

    void update(int tick);

    void start(int tick);

  public:
    void setOrigin(sf::IntRect const & rect);
    sf::IntRect const & getOrigin() const;

    std::vector<int> const & getIndexs() const;
    std::vector<int> & getIndexs();

    void setIndexs(std::vector<int> const & idxs);

    void setLoop(bool bo);
    bool getLoop() const;

    void setMaxTime(int time);
    int getMaxTime() const;

    int getStartTick() const;

    void setMapFrame(std::vector<sf::IntRect> map);

  private:
    sf::IntRect origin;
    std::vector<int> indexs;
    int actual_i;
    int start_tick;
    int max_time;
    bool loop;
    std::vector<sf::IntRect> mapFrame;
  };
};

#endif //ZAPPY_GRAPHIC_FRAME_HH
