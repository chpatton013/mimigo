#include "universe.h"
#include "../scene_hierarchy/root_node.h"
#include "../core/camera.h"

void Universe::Update() {
   camera_->Update();
}

void Universe::Draw() {
   RootNode::Instance()->Draw();
   camera_->SetView();
}

void Universe::OnLeftButtonDown() {
   printf("left --pushed\n");
}

void Universe::OnLeftButtonUp() {
   printf("left --released\n");
}

void Universe::OnRightButtonDown() {
   printf("right --pushed\n");
}

void Universe::OnRightButtonUp() {
   printf("right --released\n");
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
