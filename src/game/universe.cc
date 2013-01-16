#include "universe.h"
#include "scene_hierarchy/root_node.h"
#include "core/camera.h"

void Universe::Update() {
   camera_->Update();
   player_->Update();
   if (player_->EntersGravityFieldOf(planet_))
      player_->TransitionTo(planet_);
   else if (player_->EntersGravityFieldOf(planet2_))
      player_->TransitionTo(planet2_);
   else if (player_->EntersGravityFieldOf(planet3_))
      player_->TransitionTo(planet3_);
}

void Universe::Draw() {
   camera_->SetView();
   RootNode::Instance()->Draw();
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
