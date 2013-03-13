#ifndef _UNIVERSE_H_
#define _UNIVERSE_H_

#include "assets.h"
#include <map>
#include <vector>
#include "particleSys.h"
#include "planet.h"
#include "../core/direction_light.h"
#include "../core/entity.h"
#include "../core/light.h"
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
class TestObj;

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
   void LoadInAssets();
   void ParseAsteroidFile();
   void ParseEntityFile();
   void ParseAssetsFile();
   void ParseCheckPointsFile();
   void ParsePlanetFile();
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

   void GetBounds(glm::vec3* min, glm::vec3* max);

   std::map<std::string, std::vector<Event> > event_map_;
   std::map<std::string, EntityComponent*> entity_data_;
   std::map<std::string, int> entity_num_;
   std::map<std::string, EntityComponentNode> world_elements_;

   Camera* camera_;
   GamePlayType game_play_type_;
   std::vector<Planet*> planets_;
   std::set<Entity*> entities_;
   std::vector<Assets*> assets_;
   Player* player_;
   ParticleSystem* ps;
   Light* light_;
   int currentCheckpoint;
   float checkpoint_angle;
};

#endif
