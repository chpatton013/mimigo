#include "root_node.h"

RootNode* RootNode::root_;

void RootNode::Draw() {
   MatrixStack transform;
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it) {
      (*it)->Draw(&transform);
   }
}

void RootNode::RemoveChild(SceneNode* child) {
   children_.erase(child);
   delete child;
}
