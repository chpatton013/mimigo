#ifndef _PLANET_H_
#define _PLANET_H_

#include "scene_hierarchy/scene_node.h"
#include "scene_hierarchy/root_node.h"

class Planet {
  public:
   enum PlanetType { PLANET_TYPE_SMALL, PLANET_TYPE_LARGE };

   Planet(PlanetType planet_type, const std::string& id,
          const glm::vec3& center, float radius, float gravity_radius) :
      planet_type_(planet_type),
      center_(center),
      radius_(radius),
      gravity_radius_(gravity_radius)
   {
      Initialize(id);
   }

   bool PositionWithinGravityField(const glm::vec3& position);

   const glm::vec3 &center() const { return center_; }
   float radius() const { return radius_; }
   virtual PlanetType get_type() const { return planet_type_; }
   virtual bool is_small_planet() const
     { return planet_type_ == PLANET_TYPE_SMALL; }

  private:
   void Initialize(const std::string& id);

   PlanetType planet_type_;
   glm::vec3 center_;
   float radius_;
   float gravity_radius_;
};

#endif
