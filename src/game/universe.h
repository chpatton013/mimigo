#ifndef _UNIVERSE_H_
#define _UNIVERSE_H_

#include "../core/game.h"
#include "player.h"
#include "small_planet.h"

class RootNode;
class Camera;

class Universe : public Game {
  public:
   Universe(Camera* camera) :
      camera_(camera),
      planet_(new SmallPlanet()),
      player_(new Player(planet_))
   {
      player_->attach_planet(planet_);
   }

   virtual void Update();
   virtual void Draw();
   virtual void OnLeftButtonDown();
   virtual void OnLeftButtonUp();
   virtual void OnRightButtonDown();
   virtual void OnRightButtonUp();
   virtual void OnDownButtonDown();
   virtual void OnDownButtonUp();
   virtual void OnUpButtonDown();
   virtual void OnUpButtonUp();

  private:
   Camera* camera_;
   SmallPlanet* planet_;
   Player* player_;
};

#endif
