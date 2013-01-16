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
   RootNode::Instance()->Draw();
   camera_->SetView();
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
}

void Universe::OnUpButtonUp() {
   printf("up --released\n");
}

void Universe::OnDownButtonUp() {
   printf("down --released\n");
}

void Universe::OnDownButtonDown() {
}

void Universe::OnJumpButtonUp() {
}

void Universe::OnJumpButtonDown() {
   player_->Jump();
}
