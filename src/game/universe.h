#ifndef _UNIVERSE_H_
#define _UNIVERSE_H_

#include "../core/game.h"
#include "player.h"
#include "small_planet.h"
#include "large_planet.h"

class RootNode;
class Camera;

class Universe : public Game {
  public:
   Universe(Camera* camera) :
      camera_(camera)
   {
      planets_.push_back(new SmallPlanet("1", glm::vec3(-0.5f, -0.5f, 0.0f), 0.4f, 0.7f));
      planets_.push_back(new SmallPlanet("2", glm::vec3(.25f, .20f, 0.0f), .3f, 0.6f));
      planets_.push_back(new SmallPlanet("3", glm::vec3(-0.5f, 0.5f, 0.0f), 0.4f, 0.7f));
      planets_.push_back(new SmallPlanet("4", glm::vec3(0.30f, 1.0f, 0.0f), 0.4f, 0.7f));
      planets_.push_back(new LargePlanet("5", glm::vec3(0.0f, 25.0f, 0.0f), 20.0f, 25.0f));
      player_ = new Player(planets_[0]);
      player_->attach_planet(planets_[0]);
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

   virtual void OnCameraUpDown();
   virtual void OnCameraDownDown();

  private:
   Camera* camera_;
   std::vector<SmallPlanet*> planets_;
   Player* player_;
};

#endif
