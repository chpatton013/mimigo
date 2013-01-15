#include "universe.h"
#include "../scene_hierarchy/root_node.h"
#include "../core/camera.h"

void Universe::Update() {
   camera_->Update();
   player_->Update();
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
   printf("up --pushed\n");
}

void Universe::OnUpButtonUp() {
   printf("up --released\n");
}

void Universe::OnDownButtonUp() {
   printf("down --released\n");
}

void Universe::OnDownButtonDown() {
   printf("down --pushed\n");
}

void Universe::OnJumpButtonUp() {
}

void Universe::OnJumpButtonDown() {
   player_->Jump();
}
