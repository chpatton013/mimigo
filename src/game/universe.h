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
   Universe(Camera* camera);

   virtual void Update();
   virtual void Draw();

   // Input handling //
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
   // Input handling //

  private:
   void MakePlanets();
   void PlayerEntersGravityFieldOf(SmallPlanet* planet);
   void CheckPlayerChangesGravityFields();
   void OnMovementButtonUp();

   Camera* camera_;
   std::vector<SmallPlanet*> planets_;
   Player* player_;
};

#endif
