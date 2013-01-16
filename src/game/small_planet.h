#ifndef _SMALL_PLANET_H_
#define _SMALL_PLANET_H_

#include "scene_hierarchy/scene_node.h"
#include "scene_hierarchy/root_node.h"

class SmallPlanet {
  public:
   SmallPlanet(const glm::vec3& center, float radius) :
      center_(center),
      radius_(radius)
   {
      SceneNode* mesh = new SceneNode("small_planet");
      mesh->set_transformation(glm::translate(center));
      mesh->apply_transformation(glm::scale(radius, radius, 1.0f));
      RootNode::Instance()->AddChild(mesh);
      mesh->AddChild(SceneNode::Get("planet"));
   }
   const glm::vec3 &center() const { return center_; }
   float radius() const { return radius_; }

  private:
   glm::vec3 center_;
   float radius_;
};

#endif
