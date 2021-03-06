#ifndef _PLANET_H_
#define _PLANET_H_

#include "scene_hierarchy/scene_node.h"
#include "scene_hierarchy/root_node.h"
#include "../spatial_hierarchy/collidable_entity.h"
#include "../spatial_hierarchy/spherical_bounding_region.h"

enum PlanetType { PLANET_TYPE_SMALL, PLANET_TYPE_LARGE };
class Planet : public CollidableEntity {
  public:
   Planet(PlanetType planet_type, const std::string& id,
          const glm::vec3& center, float radius, float gravity_radius) :
      planet_type_(planet_type),
      center_(center),
      move_center(center),
      radius_(radius),
      gravity_radius_(gravity_radius),
      id_(id)
   {
      Initialize(id);

      set_bounding_region(new SphericalBoundingRegion(center, radius));
   }

   bool PositionWithinGravityField(const glm::vec3& position);

   const glm::vec3 &center() const { return center_; }
   float radius() const { return radius_; }
   float gravity_radius() const { return gravity_radius_; }
   virtual PlanetType get_type() const { return planet_type_; }
   bool is_small_planet() const
     { return planet_type_ == PLANET_TYPE_SMALL; }
   bool is_large_planet() const
     { return planet_type_ == PLANET_TYPE_LARGE; }
   const std::string& id() const { return id_; }
   int type(){ return 2;}
   
   void Pogo(float distance);
   void sideways(float distance);
   void Right();

  private:
   void Initialize(const std::string& id);

   PlanetType planet_type_;
   glm::vec3 center_;
   glm::vec3 move_center;
   float radius_;
   float gravity_radius_;
   std::string id_;
   
   bool turn;
   SceneNode *mesh;
   
};

#endif
