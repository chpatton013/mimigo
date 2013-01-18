#include "universe.h"
#include "scene_hierarchy/root_node.h"
#include "core/camera.h"
#include <iostream>
#include <fstream>
#include <sstream>

void ParsePlanetFile(const std::string& filename, std::vector<SmallPlanet*> *planets) {
   std::ifstream in;
   in.open(filename.c_str());

   bool small_planets = true;

   std::string line;
   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else if (line[0] == 'S') {
         small_planets = true;
      }
      else if (line[0] == 'L') {
         small_planets = false;
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
         if (small_planets) {
            planets->push_back(new SmallPlanet(id, position, radius, gravity_radius));
         }
         else {
            planets->push_back(new LargePlanet(id, position, radius, gravity_radius));
         }
      }
   }
}

void Universe::MakePlanets() {
   ParsePlanetFile("planets.lvl", &planets_);
}

Universe::Universe(Camera* camera) :
   camera_(camera)
{
   MakePlanets();
   player_ = new Player(planets_[0]);
}

void Universe::PlayerEntersGravityFieldOf(SmallPlanet* planet) {
   player_->TransitionTo(planet);
   if (!(planet)->is_small_planet()) {
      camera_->TransitionToLargePlanetMode();
      player_->register_observer(camera_);
   }
}

void Universe::CheckPlayerChangesGravityFields() {
   for (std::vector<SmallPlanet*>::iterator it = planets_.begin();
         it != planets_.end(); ++it) {
      if (player_->EntersGravityFieldOf(*it)) {
         PlayerEntersGravityFieldOf(*it);
         break; // Since we found a change already, we don't check the rest.
      }
   }
}

void Universe::Update() {
   camera_->Update();
   player_->Update();

   CheckPlayerChangesGravityFields();
}

void Universe::Draw() {
   camera_->SetView();
   RootNode::Instance()->Draw();
}

void Universe::OnCameraDownDown() {
   camera_->move(glm::vec3(0.0f, -1.0f, 0.0f));
}

void Universe::OnCameraUpDown() {
   camera_->move(glm::vec3(0.0f, 1.0f, 0.0f));
}

void Universe::OnLeftButtonDown() {
   player_->StartMovingLeftAroundAttachedPlanet(camera_->position());
}

void Universe::OnRightButtonDown() {
   player_->StartMovingRightAroundAttachedPlanet(camera_->position());
}

void Universe::OnUpButtonDown() {
   player_->StartMovingUpAroundAttachedPlanet(camera_->position());
}

void Universe::OnDownButtonDown() {
   player_->StartMovingDownAroundAttachedPlanet(camera_->position());
}

void Universe::OnLeftButtonUp()  { OnMovementButtonUp(); }
void Universe::OnRightButtonUp() { OnMovementButtonUp(); }
void Universe::OnUpButtonUp()    { OnMovementButtonUp(); }
void Universe::OnDownButtonUp()  { OnMovementButtonUp(); }

void Universe::OnMovementButtonUp() {
   player_->StopMoving();
}

void Universe::OnJumpButtonDown() { player_->Jump(); }
void Universe::OnJumpButtonUp() {}
