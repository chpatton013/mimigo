#include "universe.h"
#include "sdl/sdl_event_loop.h"
#include "asteroid.h"
#include "player.h"
#include "scene_hierarchy/root_node.h"
#include "small_planet_camera.h"
#include <iostream>
#include <fstream>
#include <sstream>

void ParsePlanetFile(const std::string& filename, std::vector<Planet*> *planets) {
   std::ifstream in;
   in.open(filename.c_str());

   PlanetType planet_type = PLANET_TYPE_SMALL;

   std::string line;
   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else if (line[0] == 'S') {
         planet_type = PLANET_TYPE_SMALL;
      }
      else if (line[0] == 'L') {
         planet_type = PLANET_TYPE_LARGE;
      }
      else {
         std::string id;
         glm::vec3 position;
         float radius, gravity_radius;
         stream >> id;
         stream >> position.x;
         stream >> position.y;
         stream >> position.z;
         stream >> radius;
         stream >> gravity_radius;
         planets->push_back(new Planet(planet_type, id, position, radius, gravity_radius));
      }
   }
}

void Universe::LoadInPlanets() {
   ParsePlanetFile("planets.lvl", &planets_);
}

Universe::Universe() :
   game_play_type_(GAME_PLAY_SMALL)
{
   camera_ = new SmallPlanetCamera();
   LoadInPlanets();
   player_ = new Player(planets_[0], camera_);
   EventLoop::Instance()->StartNewTimer(this, "1", 0.5f);
   EventLoop::Instance()->StartNewTimer(this, "2", 0.7f);
   EventLoop::Instance()->StartNewTimer(this, "3", 0.9f);
   EventLoop::Instance()->StartNewTimer(this, "4", 1.1f);
   EventLoop::Instance()->StartNewTimer(this, "5", 1.3f);
   EventLoop::Instance()->StartNewTimer(this, "6", 1.5f);
   EventLoop::Instance()->StartNewTimer(this, "7", 1.7f);
   PlayerEntersGravityFieldOf(planets_[0]);
}

static int asteroid_num = 0;

void Universe::OnExpiration(const std::string& event_name) {
   asteroids_.push_back(new Asteroid(planets_[0], 35.0f*asteroid_num++, event_name));
}

bool Universe::PlayerTransitionsFromSmallPlanetToLargePlanet(Planet* planet) {
   return planet->is_large_planet();
}

void Universe::UseLargePlanetCamera() {
}

void Universe::SwitchToLargePlanetGamePlay() {
   UseLargePlanetCamera();
   game_play_type_ = GAME_PLAY_LARGE;
}

void Universe::PlayerEntersGravityFieldOf(Planet* planet) {
   player_->TransitionTo(planet);
   if (PlayerTransitionsFromSmallPlanetToLargePlanet(planet)) {
      SwitchToLargePlanetGamePlay();
   }
}

void Universe::CheckPlayerChangesGravityFields() {
   if (player_->is_jumping()) {
      for (std::vector<Planet*>::iterator it = planets_.begin();
            it != planets_.end(); ++it) {
         if (player_->EntersGravityFieldOf(*it)) {
            PlayerEntersGravityFieldOf(*it);
            break; // Since we found a change already, we don't check the rest.
         }
      }
   }
}

void Universe::Update() {
   camera_->Update();
   player_->Update();

   std::vector<Asteroid*> to_remove;
   for (std::vector<Asteroid*>::iterator it = asteroids_.begin(); it != asteroids_.end(); ++it)
      if (!(*it)->Update())
         to_remove.push_back(*it);
   for (std::vector<Asteroid*>::iterator it = to_remove.begin(); it != to_remove.end(); ++it) {
      delete *it;
   }
   stl_util::RemoveAllOf(asteroids_, to_remove);

   CheckPlayerChangesGravityFields();
}

void Universe::Draw() {
   camera_->SetView();
   RootNode::Instance()->Draw();
}

//DEBUG METHODS
void Universe::OnCameraDownDown() {}
void Universe::OnCameraUpDown() {}
//DEBUG METHODS

void Universe::OnLeftButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnLeftButtonDown();
   else {
      player_->TurnLeft();
   }
}

void Universe::OnRightButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnRightButtonDown();
   else {
      player_->TurnRight();
   }
}

void Universe::OnUpButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnUpButtonDown();
   else {
      player_->MoveForward();
   }
}

void Universe::OnDownButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnDownButtonDown();
   else {
      player_->MoveBackward();
   }
}

void Universe::OnLeftButtonUp()  { player_->OnLeftButtonUp(); }
void Universe::OnRightButtonUp() { player_->OnRightButtonUp(); }
void Universe::OnUpButtonUp()    { player_->OnUpButtonUp(); }
void Universe::OnDownButtonUp()  { player_->OnDownButtonUp(); }

void Universe::OnJumpButtonDown() {
   player_->Jump();
}
void Universe::OnJumpButtonUp() {
   player_->ReleaseJump();
}
