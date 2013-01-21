#include "universe.h"
#include "player.h"
#include "scene_hierarchy/root_node.h"
#include "core/camera.h"
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

Universe::Universe(Camera* camera) :
   camera_(camera),
   game_play_type_(GAME_PLAY_SMALL)
{
   LoadInPlanets();
   player_ = new Player(planets_[0]);
   PlayerEntersGravityFieldOf(planets_[0]);
}

bool Universe::PlayerTransitionsFromSmallPlanetToLargePlanet(Planet* planet) {
   return planet->is_large_planet();
}

void Universe::UseLargePlanetCamera() {
   camera_->TransitionToLargePlanetMode();
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
   player_->Update();
   camera_->Update(player_->position());

   CheckPlayerChangesGravityFields();
}

void Universe::Draw() {
   camera_->SetView();
   RootNode::Instance()->Draw();
}

//DEBUG METHODS
void Universe::OnCameraDownDown() { camera_->move(glm::vec3(0.0f, -1.0f, 0.0f)); }
void Universe::OnCameraUpDown() { camera_->move(glm::vec3(0.0f, 1.0f, 0.0f)); }
//DEBUG METHODS

void Universe::OnLeftButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnLeftButtonDown(camera_->position());
   else {
      player_->TurnLeft();
   }
}

void Universe::OnRightButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnRightButtonDown(camera_->position());
   else {
      player_->TurnRight();
   }
}

void Universe::OnUpButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnUpButtonDown(camera_->position());
   else {
      player_->MoveForward();
   }
}

void Universe::OnDownButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnDownButtonDown(camera_->position());
   else {
      //player_->MoveBackward();
   }
}

void Universe::OnLeftButtonUp()  { OnMovementButtonUp(); }
void Universe::OnRightButtonUp() { OnMovementButtonUp(); }
void Universe::OnUpButtonUp()    { OnMovementButtonUp(); }
void Universe::OnDownButtonUp()  { OnMovementButtonUp(); }

void Universe::OnMovementButtonUp() { player_->StopMoving(); }

void Universe::OnJumpButtonDown() {
   if (!player_->is_jumping())
      player_->Jump();
}
void Universe::OnJumpButtonUp() {
   player_->ReleaseJump();
}
