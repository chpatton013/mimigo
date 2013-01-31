#include "collision_node.h"
#include "collision.h"

bool CollisionNode::TestCollision(CollisionNode& other) {
   if (Collision::CheckCollision(
         this->GetBoundingRegion(),
         other.GetBoundingRegion()
         ) == SEPARATE) {
      return false;
   }

   // TODO: check children of `this` and `other` for intersections
   return true;
}
