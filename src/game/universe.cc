#include "universe.h"
#include "../scene_hierarchy/root_node.h"

void Universe::Update() {
   std::cout << "update" << std::endl;
}

void Universe::Draw() {
   std::cout << "draw" << std::endl;
   RootNode::Instance()->Draw();
}
