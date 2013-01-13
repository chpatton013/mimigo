#ifndef _UNIVERSE_H_
#define _UNIVERSE_H_

#include "../core/game.h"

class RootNode;
class Camera;

class Universe : public Game {
  public:
   Universe(Camera* camera) :
      camera_(camera)
   {}

   virtual void Update();
   virtual void Draw();
  private:
   Camera* camera_;
};

#endif
