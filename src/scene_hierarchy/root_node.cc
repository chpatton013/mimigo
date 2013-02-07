#include "root_node.h"

#include <iostream>
#include <sstream>

RootNode* RootNode::root_;

void RootNode::Draw() {
   MatrixStack transform;
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it) {
      (*it)->Draw(&transform);
   }
}

void RootNode::AddChild(SceneNode* child) {
   SceneNode::AddChild(child);
}

void RootNode::RemoveChild(SceneNode* child) {
   assert(child != NULL);
   DestroyChild(child);
}
