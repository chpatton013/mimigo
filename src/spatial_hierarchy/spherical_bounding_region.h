#ifndef _SPHERICAL_BOUNDING_REGION_H_
#define _SPHERICAL_BOUNDING_REGION_H_

#include <glm/glm.hpp>
#include "bounding_region.h"

class SphericalBoundingRegion : public BoundingRegion {
  public:
   SphericalBoundingRegion(const glm::vec3& c, float r);
   virtual ~SphericalBoundingRegion();

   virtual glm::vec3 center();
   virtual float radius();
   virtual glm::vec3 min();
   virtual glm::vec3 max();

   virtual void set_center(const glm::vec3& c);
   virtual void set_radius(float r);

   virtual void print();

  protected:
   glm::vec3 center_;
   float radius_;
};

#endif
