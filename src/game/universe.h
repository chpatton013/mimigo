#ifndef _UNIVERSE_H_
#define _UNIVERSE_H_

/*<<<<<<< HEAD
#include "../core/game.h"
#include "../core/timer.h"
#include "logic_puzzle.h"
#include "planet.h"
#include "particles.h"
#include "assets.h"
=======
>>>>>>> 84ba2141e3c518655025bcf1f6bcc5808e0012da
*/

#include "assets.h"
#include <map>
#include <vector>
#include "particles.h"
#include "particleSys.h"
#include "planet.h"
#include "../core/entity.h"
#include "../core/game.h"
#include "../core/timer.h"
#include "../scene_hierarchy/root_node.h"
#include "../spatial_hierarchy/spatial_manager.h"
#include "../spatial_hierarchy/collidable_entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>

class Asteroid;
class SwingAsteroid;
class SpatialManager;
class Camera;
class Player;

struct Event {
   Event(std::string event_name, float delay) :
      event_name(event_name),
      delay(delay)
   {}
   std::string event_name;
   float delay;
};

enum GamePlayType { GAME_PLAY_SMALL, GAME_PLAY_LARGE, GAME_PLAY_TRANSITION };
class Universe : public Game,
                 public Timer::Delegate {
  public:
void print_vec(const glm::vec3& v) {
   printf("[%.2f,%.2f,%.2f]\n", v.x, v.y, v.z);
}
   Universe();

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

   virtual void OnExpiration(const std::string& event_name);
   virtual void OnEvent(const std::string& event);

  private:
   void LoadInPlanets();
   void ParseAsteroidFile();
   void PlayerEntersGravityFieldOf(Planet* planet);
   bool PlayerTransitionsFromSmallPlanetToLargePlanet(Planet* planet);
   void SwitchToLargePlanetGamePlay();

   bool is_small_planet_gameplay() const
    { return game_play_type_ == GAME_PLAY_SMALL; }
   bool is_large_planet_gameplay() const
    { return game_play_type_ == GAME_PLAY_LARGE; }

   void CheckPlayerChangesGravityFields();
   void OnMovementButtonUp();
   void UseLargePlanetCamera();

   std::map<std::string, std::vector<Event> > event_map_;

   Camera* camera_;
   GamePlayType game_play_type_;
   std::vector<Planet*> planets_;
   std::set<Entity*> entities_;
   //std::vector<Particles*> particles_;
   std::vector<Assets*> assets_;
   Player* player_;
   ParticleSystem* ps;
};

#endif
