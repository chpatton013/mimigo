#include "universe.h"
#include "../scene_hierarchy/root_node.h"

void Universe::Update() {
}

void Universe::Draw() {
   RootNode::Instance()->Draw();
}
