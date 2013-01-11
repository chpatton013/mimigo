#include "universe.h"
#include "../scene_hierarchy/root_node.h"

void Universe::Update() {
   std::cout << "update" << std::endl;
}

void Universe::Draw() {
   RootNode::Instance()->Draw();
}
