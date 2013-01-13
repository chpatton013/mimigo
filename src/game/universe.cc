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
