#include "universe.h"
#include "scene_hierarchy/root_node.h"
#include "core/camera.h"

void Universe::MakePlanets() {
   //TODO: Meta data candidate
   planets_.push_back(new SmallPlanet("1", glm::vec3(-0.5f, -0.5f, 0.0f), 0.4f, 0.7f));
   planets_.push_back(new SmallPlanet("2", glm::vec3(.25f, .20f, 0.0f), .3f, 0.6f));
   planets_.push_back(new SmallPlanet("3", glm::vec3(-0.5f, 0.5f, 0.0f), 0.4f, 0.7f));
   planets_.push_back(new SmallPlanet("4", glm::vec3(0.30f, 1.0f, 0.0f), 0.4f, 0.7f));
   planets_.push_back(new LargePlanet("5", glm::vec3(0.0f, 25.0f, 0.0f), 20.0f, 25.0f));
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

void Universe::OnLeftButtonUp() { OnMovementButtonUp(); }
void Universe::OnRightButtonUp() { OnMovementButtonUp(); }
void Universe::OnUpButtonUp() { OnMovementButtonUp(); }
void Universe::OnDownButtonUp() { OnMovementButtonUp(); }
void Universe::OnMovementButtonUp() {
   player_->StopMoving();
}

void Universe::OnJumpButtonUp() {
   camera_->DebugPrint(); // TODO: Remove this
}

void Universe::OnJumpButtonDown() {
   player_->Jump();
}
