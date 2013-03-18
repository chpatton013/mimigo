#ifndef _BOUNDING_REGION_H_
#define _BOUNDING_REGION_H_

#include <string>
#include <glm/glm.hpp>
#include "bounding_region_component.h"
#include "../core/rotation.h"
#include "../gl/gl_mesh.h"
#include "../scene_hierarchy/entity_component_node.h"

class BoundingRegion {
  public:
   BoundingRegion();
   virtual ~BoundingRegion();

   virtual glm::vec3 center() = 0;
   virtual glm::vec3 min() = 0;
   virtual glm::vec3 max() = 0;

   virtual void set_center(const glm::vec3& c) = 0;

   virtual void print() = 0;

  protected:
   BoundingRegionComponent* brc_;
   std::string name_;

   virtual void create_component(
      const glm::vec3& t,
      const Rotation& r,
      const glm::vec3& s,
      GLMesh* mesh
   );

   virtual void delete_component();
};

#endif
