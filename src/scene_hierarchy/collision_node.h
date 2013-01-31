#ifndef _COLISION_NODE_H_
#define _COLISION_NODE_H_

#include "bounding_region.h"
#include "scene_node.h"

class CollisionNode : public SceneNode {
  public:
   bool TestCollision(CollisionNode& other);
};

#endif
