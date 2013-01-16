#include "universe.h"
#include "scene_hierarchy/root_node.h"
#include "core/camera.h"

void Universe::Update() {
   camera_->Update();
   player_->Update();

   for (std::vector<SmallPlanet*>::iterator it = planets_.begin();
         it != planets_.end(); ++it) {
      if (player_->EntersGravityFieldOf(*it)) {
         player_->TransitionTo(*it);
         break;
      }
   }
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
   player_->StartMovingLeftAroundAttachedPlanet();
}

void Universe::OnLeftButtonUp() {
   player_->StopMoving();
}

void Universe::OnRightButtonDown() {
   player_->StartMovingRightAroundAttachedPlanet();
}

void Universe::OnRightButtonUp() {
   player_->StopMoving();
}

void Universe::OnUpButtonDown() {
   player_->StartMovingUpAroundAttachedPlanet();
}

void Universe::OnUpButtonUp() {
   player_->StopMoving();
}

void Universe::OnDownButtonUp() {
   player_->StopMoving();
}

void Universe::OnDownButtonDown() {
   player_->StartMovingDownAroundAttachedPlanet();
}

void Universe::OnJumpButtonUp() {
}

void Universe::OnJumpButtonDown() {
   player_->Jump();
}
