#ifndef _UNIVERSE_H_
#define _UNIVERSE_H_

#include "core/game.h"

class Universe : public Game {
  public:
   virtual void Update();
   virtual void Draw();
};

#endif
