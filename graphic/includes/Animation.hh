//
// Created by rottaf on 6/14/16.
//

#ifndef ZAPPY_GRAPHIC_ANIMATION_HH
#define ZAPPY_GRAPHIC_ANIMATION_HH


#include <map>
#include "Frame.hh"

namespace zappy {
  class Animation {
  public:
    Animation();
    ~Animation();

  private:
    std::map<std::string, Frame> type;
  };
};

#endif //ZAPPY_GRAPHIC_ANIMATION_HH
