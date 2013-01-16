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
      planet_(new SmallPlanet("1", glm::vec3(-0.5f, -0.5f, 0.0f), 0.4f, 0.7f)),
      player_(new Player(planet_))
   {
      player_->attach_planet(planet_);
      planet2_ = new SmallPlanet("2", glm::vec3(.25f, .25f, 0.0f), .3f, 0.6f);
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
   virtual void OnJumpButtonDown();
   virtual void OnJumpButtonUp();

  private:
   Camera* camera_;
   SmallPlanet* planet_;
   SmallPlanet* planet2_;
   Player* player_;
};

#endif
