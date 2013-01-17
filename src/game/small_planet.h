#ifndef _SMALL_PLANET_H_
#define _SMALL_PLANET_H_

#include "scene_hierarchy/scene_node.h"
#include "scene_hierarchy/root_node.h"

class SmallPlanet {
  public:
   SmallPlanet(const std::string& id, const glm::vec3& center, float radius,
               float gravity_radius) :
      center_(center),
      radius_(radius),
      gravity_radius_(gravity_radius)
   {
      Initialize(id);
   }

   bool PositionWithinGravityField(const glm::vec3& position);

   const glm::vec3 &center() const { return center_; }
   float radius() const { return radius_; }
   virtual bool is_small_planet() const { return true; }

  private:
   void Initialize(const std::string& id);

   glm::vec3 center_;
   float radius_;
   float gravity_radius_;
};

#endif
