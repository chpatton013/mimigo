#include "root_node.h"

#include <typeinfo>

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

void RootNode::CalculateCollisions() {
   collisions_.clear();

   for (std::set<SceneNode*>::iterator it1 = children_.begin();
         it1 != children_.end(); ++it1) {
      // begin inner loop just beyond where outer starts on this iteration to
      // avoid checking reversed pairs (ie: A,B / B,A)
      std::set<SceneNode*>::iterator it2 = it1;
      for (++it2; it2 != children_.end(); ++it2) {
         CollisionNode* cn1 = dynamic_cast<CollisionNode*>(*it1);
         CollisionNode* cn2 = dynamic_cast<CollisionNode*>(*it2);
         // NULL `cn1` or `cn2` indicates data integrity errors.
         // Prevent runtime error or use its presence as debugging?
         if (cn1 != NULL && cn2 != NULL && cn1->TestCollision(*cn2)) {
            collisions_.insert(
               std::make_pair((CollisionNode*)*it1, (CollisionNode*)*it2)
            );
         }
      }
   }
}
